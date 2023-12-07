#ifndef BOMBER_STUDENT_SOCKET_UDP_H
#define BOMBER_STUDENT_SOCKET_UDP_H


#include "Socket.h"

class SocketUDP : public Socket {
public:
    explicit SocketUDP(Protocol protocol);
    SocketUDP(Protocol protocol, bool enableBroadcast);
    void send(const std::string& msg, const SocketAddress& dest_addr) const;
    [[nodiscard]] std::string receive(SocketAddress* src_addr) const;
};


#endif //BOMBER_STUDENT_SOCKET_UDP_H
