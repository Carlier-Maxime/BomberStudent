#include "Socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <utility>
#include "../utils/Log.h"
#include "../utils/BomberStudentExceptions.h"

struct sockaddr_storage Socket::getSockAddrStorage(const SocketAddress& address) {
    struct sockaddr_storage addr{};
    struct sockaddr_in6 ipv6={};
    struct sockaddr_in ipv4={};
    switch (address.getProtocol()) {
        case Protocol::IPV4:
            addr.ss_family = AF_INET;
            ipv4.sin_family = AF_INET;
            ipv4.sin_port = htons(address.getPort());
            if (inet_pton(AF_INET, address.getIp().c_str(), &(ipv4.sin_addr)) <= 0) {
                throw SocketException("Conversion IPV4 address failed for "+address.getIp());
            }
            std::memcpy(&addr, &ipv4, sizeof(struct sockaddr_in));
            break;
        case Protocol::IPV6:
            ipv6.sin6_family = addr.ss_family = AF_INET6;
            ipv6.sin6_port = htons(address.getPort());
            if (inet_pton(AF_INET6, address.getIp().c_str(), &(ipv6.sin6_addr)) < 0) {
                throw SocketException("Conversion IPV6 address failed for "+address.getIp());
            }
            std::memcpy(&addr, &ipv6, sizeof(struct sockaddr_in6));
            break;
        default:
            throw SocketException("Protocol not supported");
    }
    return addr;
}

void Socket::setSocketAddress(SocketAddress* address, struct sockaddr_storage addr) {
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
            throw SocketException("Protocol not supported");
    }
    address->setIp(ipBuffer);
}

void Socket::bind(const SocketAddress &new_address) const {
    struct sockaddr_storage addr = getSockAddrStorage(new_address);
    if(::bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        close(socket_fd);
        throw IPCException("Socket couldn't bind to the port");
    }
}

Socket::Socket(int fd, SocketAddress  address) : address(std::move(address)), socket_fd(fd){}

Socket::Socket(Protocol protocol, int type, bool enableBroadcast) : address("::1", 0, protocol) {
    if ((socket_fd = socket(protocol==Protocol::IPV4 ? AF_INET : AF_INET6, type, 0)) < 0) {
        throw SocketException("create socket failed");
    }
    int broadcast = enableBroadcast;
    if (protocol==Protocol::IPV6) {
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

void Socket::setTimeout(unsigned int sec, unsigned int micro_sec) const {
    struct timeval timeout{
        sec,
        micro_sec
    };
    setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
}

const SocketAddress &Socket::getAddress() const {
    return address;
}
