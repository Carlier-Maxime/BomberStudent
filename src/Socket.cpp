#include "Socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>
#include <cstring>
#include "Log.h"
#include "BomberStudentExceptions.h"

#define BUFFER_SIZE 1024

struct sockaddr_storage getSockAddrStorage(const SocketAddress& address) {
    struct sockaddr_storage addr{};
    struct sockaddr_in6 ipv6={};
    struct sockaddr_in ipv4={};
    switch (address.getProtocol()) {
        case Protocol::IPV4:
            label_ipv4:
            addr.ss_family = AF_INET;
            ipv4.sin_family = AF_INET;
            ipv4.sin_port = htons(address.getPort());
            if (inet_pton(AF_INET, address.getIp().c_str(), &(ipv4.sin_addr)) <= 0) {
                throw SocketException("Conversion IPV4 address failed");
            }
            std::memcpy(&addr, &ipv4, sizeof(struct sockaddr_storage));
            break;
        case Protocol::IPV6:
            ipv6.sin6_family = addr.ss_family = AF_INET6;
            ipv6.sin6_port = htons(address.getPort());
            if (inet_pton(AF_INET6, address.getIp().c_str(), &(ipv6.sin6_addr)) < 0) {
                throw SocketException("Conversion IPV6 address failed");
            }
            std::memcpy(&addr, &ipv6, sizeof(struct sockaddr_storage));
            break;
        default:
            Log::warning("Protocol not supported. Switching to IPv4 protocol");
            goto label_ipv4;
    }
    return addr;
}

void setSocketAddress(SocketAddress* address, struct sockaddr_storage addr) {
    struct sockaddr_in6 ipv6={};
    struct sockaddr_in ipv4={};
    char ipBuffer[INET6_ADDRSTRLEN];
    switch (addr.ss_family) {
        case AF_INET:
            address->setProtocol(Protocol::IPV4);
            std::memcpy( &ipv4, &addr, sizeof(struct sockaddr_in));
            address->setPort(ntohs(ipv4.sin_port));
            if (!inet_ntop(AF_INET, &ipv4.sin_addr, ipBuffer, sizeof(ipBuffer))) {
                throw SocketException("Conversion IPV6 address failed");
            }
            break;
        case AF_INET6:
            address->setProtocol(Protocol::IPV6);
            std::memcpy( &ipv6, &addr, sizeof(struct sockaddr_in6));
            address->setPort(ntohs(ipv6.sin6_port));
            if (!inet_ntop(AF_INET6, &ipv6.sin6_addr, ipBuffer, sizeof(ipBuffer))) {
                throw SocketException("Conversion IPV6 address failed");
            }
            break;
        default:
            Log::error("Protocol not supported. Switching to IPv4 protocol");
    }
    address->setIp(ipBuffer);
}

Socket::Socket(const SocketAddress &address, int type, bool enableBroadcast) : address(address) {
    struct sockaddr_storage addr = getSockAddrStorage(address);
    if ((socket_fd = socket(addr.ss_family, type, 0)) < 0) {
        throw SocketException("create socket failed");
    }
    if(bind(socket_fd, (struct sockaddr*)&addr, sizeof(address)) < 0){
        close(socket_fd);
        throw IPCException("Socket couldn't bind to the port");
    }
    int broadcast = enableBroadcast;
    if (address.getProtocol()==Protocol::IPV6) {
        if (setsockopt(socket_fd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &broadcast, sizeof(broadcast)) < 0) {
            close(socket_fd);
            throw IPCException("Socket couldn't set broadcast option");
        }
    } else {
        if (setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
            close(socket_fd);
            throw IPCException("Socket couldn't set broadcast option");
        }
    }
}

Socket::~Socket() {
    close(socket_fd);
}

void Socket::send(const std::string& msg, const SocketAddress& dest_addr) const {
    struct sockaddr_storage addr = getSockAddrStorage(dest_addr);
    if (sendto(socket_fd, msg.c_str(), msg.length(), 0, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        throw SocketException("Socket can't send");
    }
}

std::string Socket::receive(SocketAddress* src_addr) const {
    struct sockaddr_storage addr = getSockAddrStorage(*src_addr);
    socklen_t src_socket_size = sizeof(addr);
    char buffer[BUFFER_SIZE];
    ssize_t bytesReceived = recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&addr, &src_socket_size);
    if (bytesReceived < 0) {
        throw SocketException("Couldn't receive");
    }
    setSocketAddress(src_addr, addr);
    return {buffer, static_cast<size_t>(bytesReceived)};
}