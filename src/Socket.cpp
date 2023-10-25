#include "Socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Log.h"

Socket::Socket(SocketAddress addr) : addr(addr) {
    struct sockaddr_in addr_in{
            AF_INET,
            htons(addr.getPort()),
            {inet_addr(addr.getIp().c_str())},
            {0,0,0,0,0,0,0,0}
    };
    if ((socket_fd = socket(addr_in.sin_family, SOCK_DGRAM, 0)) < 0) { 
        Log::error("create socket failed");
        throw std::exception();
    }
    if(bind(socket_fd, (struct sockaddr*)&addr_in, sizeof(addr_in)) < 0){
        Log::error("Socket couldn't bind to the port");
        close(socket_fd);
        throw std::exception();
    }
}

Socket::~Socket() {
    close(socket_fd);
}