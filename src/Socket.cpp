#include "Socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>
#include <cstring>
#include "Log.h"

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
                Log::system_error("Conversion IPV4 address failed");
                throw std::exception();
            }
            std::memcpy(&addr, &ipv4, sizeof(struct sockaddr_storage));
            break;
        case Protocol::IPV6:
            ipv6.sin6_family = addr.ss_family = AF_INET6;
            ipv6.sin6_port = htons(address.getPort());
            if (inet_pton(AF_INET6, address.getIp().c_str(), &(ipv6.sin6_addr)) < 0) {
                Log::system_error("Conversion IPV6 address failed");
                throw std::exception();
            }
            std::memcpy(&addr, &ipv6, sizeof(struct sockaddr_storage));
            break;
        default:
            Log::warning("Protocol not supported. Switching to IPv4 protocol");
            goto label_ipv4;
    }
    return addr;
}

Socket::Socket(const SocketAddress& address) : address(address) {
    struct sockaddr_storage addr = getSockAddrStorage(address);
    if ((socket_fd = socket(addr.ss_family, SOCK_DGRAM, 0)) < 0) {
        Log::system_error("create socket failed");
        throw std::exception();
    }
    if(bind(socket_fd, (struct sockaddr*)&addr, sizeof(address)) < 0){
        Log::system_error("Socket couldn't bind to the port");
        close(socket_fd);
        throw std::exception();
    }
}

Socket::~Socket() {
    close(socket_fd);
}

void Socket::send(const std::string& msg, const SocketAddress& dest_addr) const {
    struct sockaddr_storage addr = getSockAddrStorage(dest_addr);
    if (sendto(socket_fd, msg.c_str(), msg.length(), 0, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        Log::system_error("Socket can't send");
        throw std::exception();
    }
}

std::string Socket::receive(const SocketAddress& src_addr) const {
    struct sockaddr_storage addr = getSockAddrStorage(src_addr);
    socklen_t src_socket_size = sizeof(addr);
    char buffer[BUFFER_SIZE];
    ssize_t bytesReceived = recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&addr, &src_socket_size);
    if (bytesReceived < 0) {
        Log::system_error("Couldn't receive");
        throw std::exception();
    }
    return {buffer, static_cast<size_t>(bytesReceived)};
}