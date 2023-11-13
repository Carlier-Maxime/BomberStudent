#ifndef BOMBER_STUDENT_SOCKET_H
#define BOMBER_STUDENT_SOCKET_H

#include <string>
#include "SocketAddress.h"

class Socket {
private:
    SocketAddress address;
protected:
    int socket_fd;
    static void setSocketAddress(SocketAddress* address, struct sockaddr_storage addr);
    static struct sockaddr_storage getSockAddrStorage(const SocketAddress& address);
public:
    Socket(const SocketAddress& address, int type, bool enableBroadcast);
    void send(const std::string& msg, const SocketAddress& dest_addr) const;
    [[nodiscard]] std::string receive(SocketAddress* src_addr) const;
    ~Socket();
};

#endif //BOMBER_STUDENT_SOCKET_H