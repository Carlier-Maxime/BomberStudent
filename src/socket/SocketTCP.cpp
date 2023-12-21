#include <sys/socket.h>
#include <utility>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include "SocketTCP.h"
#include "../utils/BomberStudentExceptions.h"
#include "../utils/Config.h"

#define BUFFER_SIZE 1024

SocketTCP::SocketTCP(Protocol protocol) : Socket(protocol, SOCK_STREAM, false) {
    int flag = 1;
    setsockopt(socket_fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
}

void SocketTCP::connect(const SocketAddress& address) {
    struct sockaddr_storage addr = Socket::getSockAddrStorage(address);
    if (::connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr))==-1) throw SocketException("Socket connection failed");
}

SocketTCP* SocketTCP::accept() {
    struct sockaddr_storage addr{};
    socklen_t size = sizeof(addr);
    int fd;
    if ((fd=::accept(socket_fd, (struct sockaddr*)&addr, &size))==-1) throw SocketException("Socket Acceptation failed");
    SocketAddress address = SocketAddress("::", 0);
    Socket::setSocketAddress(&address, addr);
    return new SocketTCP(fd, address);
}

void SocketTCP::listen(int lenQueue) {
    if (::listen(socket_fd, lenQueue) == -1) {
        throw SocketException("Error during listen in socket");
    }
}

SocketTCP::SocketTCP(int fd, SocketAddress address) : Socket(fd, std::move(address)) {
    int flag = 1;
    setsockopt(socket_fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
}

void SocketTCP::send(const std::string& msg) const {
    if (::send(socket_fd, (msg+Config::getMsgSeparator()).c_str(), msg.length()+1, 0) < 0) {
        throw SocketException("Socket can't send");
    }
}

std::string SocketTCP::receive() const {
    char buffer[BUFFER_SIZE];
    ssize_t bytesReceived = recv(socket_fd, buffer, BUFFER_SIZE, 0);
    if (bytesReceived < 0) {
        throw SocketException("Couldn't receive");
    }
    return {buffer, static_cast<size_t>(bytesReceived)};
}
