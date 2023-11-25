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
    Socket(int fd, SocketAddress  address);
public:
    Socket(Protocol protocol, int type, bool enableBroadcast);
    void bind(const SocketAddress& new_address) const;
    void send(const std::string& msg, const SocketAddress& dest_addr) const;
    [[nodiscard]] std::string receive(SocketAddress* src_addr) const;
    void setTimeout(unsigned sec, unsigned micro_sec) const;
    ~Socket();
};

#endif //BOMBER_STUDENT_SOCKET_H