#include "Socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Log.h"

#define BUFFER_SIZE 1024

struct sockaddr_in getSockAddrIn(const SocketAddress& addr) {
    return {
        AF_INET,
        htons(addr.getPort()),
        {inet_addr(addr.getIp().c_str())},
        {0,0,0,0,0,0,0,0}
    };
}

Socket::Socket(SocketAddress addr) : addr(addr) {
    struct sockaddr_in addr_in = getSockAddrIn(addr);
    if ((socket_fd = socket(addr_in.sin_family, SOCK_DGRAM, 0)) < 0) { 
        Log::system_error("create socket failed");
        throw std::exception();
    }
    if(bind(socket_fd, (struct sockaddr*)&addr_in, sizeof(addr_in)) < 0){
        Log::system_error("Socket couldn't bind to the port");
        close(socket_fd);
        throw std::exception();
    }
}

Socket::~Socket() {
    close(socket_fd);
}

void Socket::send(std::string msg, const SocketAddress& dest_addr) {
    struct sockaddr_in addr_in = getSockAddrIn(dest_addr);
    if (sendto(socket_fd, msg.c_str(), msg.length(), 0, (struct sockaddr*)&addr_in, sizeof(addr_in)) < 0) {
        Log::system_error("Socket can't send");
        throw std::exception();
    }
}

std::string Socket::receive(const SocketAddress& src_addr) {
    struct sockaddr_in addr_in = getSockAddrIn(src_addr);
    socklen_t src_socket_size = sizeof(addr_in);
    char buffer[BUFFER_SIZE];
    if (recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&addr_in, &src_socket_size) < 0) {
        Log::system_error("Couldn't receive");
        throw std::exception();
    }
    return std::string(buffer);
}