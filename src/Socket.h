#ifndef BOMBER_STUDENT_SOCKET_H
#define BOMBER_STUDENT_SOCKET_H

#include <string>
#include "SocketAddress.h"

class Socket {
private:
    SocketAddress address;
    int socket_fd;
public:
    explicit Socket(const SocketAddress& address);
    void send(const std::string& msg, const SocketAddress& dest_addr) const;
    [[nodiscard]] std::string receive(SocketAddress* src_addr) const;
    ~Socket();
};

#endif //BOMBER_STUDENT_SOCKET_H