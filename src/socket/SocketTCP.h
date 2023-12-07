#ifndef BOMBER_STUDENT_SOCKET_TCP_H
#define BOMBER_STUDENT_SOCKET_TCP_H


#include "Socket.h"

class SocketTCP : public Socket {
private:
    SocketTCP(int fd, SocketAddress address);
public:
    explicit SocketTCP(Protocol protocol);
    void listen(int lenQueue);
    void connect(const SocketAddress& address);
    [[nodiscard]] SocketTCP* accept();
    void send(const std::string& msg) const;
    [[nodiscard]] std::string receive() const;
};


#endif //BOMBER_STUDENT_SOCKET_TCP_H
