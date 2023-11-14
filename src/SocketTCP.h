#ifndef BOMBER_STUDENT_SOCKET_TCP_H
#define BOMBER_STUDENT_SOCKET_TCP_H


#include "Socket.h"

class SocketTCP : public Socket {
public:
    SocketTCP(Protocol protocol);
    void listen(int lenQueue);
    void connect(const SocketAddress& address);
    SocketAddress accept();
};


#endif //BOMBER_STUDENT_SOCKET_TCP_H
