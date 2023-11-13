#ifndef BOMBER_STUDENT_SOCKET_TCP_H
#define BOMBER_STUDENT_SOCKET_TCP_H


#include "Socket.h"

class SocketTCP : public Socket {
public:
    explicit SocketTCP(const SocketAddress& address);
    void connect(const SocketAddress& address);
    SocketAddress accept();
};


#endif //BOMBER_STUDENT_SOCKET_TCP_H
