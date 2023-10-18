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
    ~Socket();
};

#endif //BOMBER_STUDENT_SOCKET_H