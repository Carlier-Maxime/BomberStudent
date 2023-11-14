#ifndef BOMBER_STUDENT_SOCKET_UDP_H
#define BOMBER_STUDENT_SOCKET_UDP_H


#include "Socket.h"

class SocketUDP : public Socket {
public:
    explicit SocketUDP(Protocol protocol);
    SocketUDP(Protocol protocol, bool enableBroadcast);
};


#endif //BOMBER_STUDENT_SOCKET_UDP_H
