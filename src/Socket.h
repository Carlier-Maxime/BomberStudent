#ifndef BOMBER_STUDENT_SOCKET_H
#define BOMBER_STUDENT_SOCKET_H

#include <string>
#include "SocketAddress.h"

class Socket {
private:
    SocketAddress addr;
    int socket_fd;
public:
    explicit Socket(const SocketAddress& addr);
    void send(const std::string& msg, const SocketAddress& dest_addr) const;
    [[nodiscard]] std::string receive(const SocketAddress& src_addr) const;
    ~Socket();
};

#endif //BOMBER_STUDENT_SOCKET_H