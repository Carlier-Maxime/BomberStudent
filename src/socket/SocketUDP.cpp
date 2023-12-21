#include <sys/socket.h>
#include "SocketUDP.h"
#include "../utils/BomberStudentExceptions.h"
#include "../utils/Config.h"

#define BUFFER_SIZE 1024

SocketUDP::SocketUDP(Protocol protocol) : Socket(protocol, SOCK_DGRAM, false) {}

SocketUDP::SocketUDP(Protocol protocol, bool enableBroadcast) : Socket(protocol, SOCK_DGRAM, enableBroadcast) {}

void SocketUDP::send(const std::string& msg, const SocketAddress& dest_addr) const {
    struct sockaddr_storage addr = getSockAddrStorage(dest_addr);
    if (sendto(socket_fd, (msg+Config::getMsgSeparator()).c_str(), msg.length()+1, 0, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        throw SocketException("Socket can't send");
    }
}

std::string SocketUDP::receive(SocketAddress* src_addr) const {
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