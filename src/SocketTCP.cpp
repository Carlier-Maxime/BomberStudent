#include <sys/socket.h>
#include <csignal>
#include "SocketTCP.h"
#include "BomberStudentExceptions.h"

SocketTCP::SocketTCP(const SocketAddress &address, bool listen) : Socket(address, SOCK_STREAM, false) {
    if (listen && ::listen(socket_fd, 5) == -1) {
        close(socket_fd);
        throw SocketException("Error during listen in socket");
    }
}

void SocketTCP::connect(const SocketAddress& address) {
    struct sockaddr_storage addr = Socket::getSockAddrStorage(address);
    if (::connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr))==-1) throw SocketException("Socket connection failed");
}

SocketAddress SocketTCP::accept() {
    struct sockaddr_storage addr;
    socklen_t size;
    if (::accept(socket_fd, (struct sockaddr*)&addr, &size)==-1) throw SocketException("Socket Acceptation failed");
    SocketAddress address = SocketAddress("::", 0);
    Socket::setSocketAddress(&address, addr);
    return address;
}