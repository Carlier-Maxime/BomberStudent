#include "Socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>

Socket::Socket(SocketAddress addr) : addr(addr) {
    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(addr.getPort());
    addr_in.sin_addr.s_addr = inet_addr(addr.getIp().c_str());
    if ((socket_fd = socket(addr_in.sin_family, SOCK_DGRAM, 0)) < 0) { 
        perror("socket failed");
        throw std::exception();
    }
    if(bind(socket_fd, (struct sockaddr*)&addr_in, sizeof(addr_in)) < 0){
        printf("Couldn't bind to the port\n");
        close(socket_fd);
        throw std::exception();
    }
}

Socket::~Socket() {
    close(socket_fd);
}