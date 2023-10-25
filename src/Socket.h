#ifndef BOMBER_STUDENT_SOCKET_H
#define BOMBER_STUDENT_SOCKET_H

#include <string>
#include "SocketAddress.h"

class Socket {
private:
    SocketAddress addr;
    int socket_fd;
public:
    Socket(SocketAddress addr);
    void send(std::string msg, const SocketAddress& dest_addr);
    std::string receive(const SocketAddress& src_addr);
    ~Socket();
};

#endif //BOMBER_STUDENT_SOCKET_H