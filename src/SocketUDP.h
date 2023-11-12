#ifndef BOMBER_STUDENT_SOCKET_UDP_H
#define BOMBER_STUDENT_SOCKET_UDP_H


#include "Socket.h"

class SocketUDP : public Socket {
public:
    explicit SocketUDP(const SocketAddress& address);
    SocketUDP(const SocketAddress &address, bool enableBroadcast);
};


#endif //BOMBER_STUDENT_SOCKET_UDP_H
