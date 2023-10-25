#ifndef BOMBER_STUDENT_SOCKET_ADDRESS_H
#define BOMBER_STUDENT_SOCKET_ADDRESS_H

#include <string>

enum class Protocol {
    IPV4,
    IPV6
};

class SocketAddress {
private:
    Protocol protocol;
    unsigned short port;
    std::string ip;
public:
    SocketAddress(std::string ip, unsigned short port, Protocol protocol);
    Protocol getProtocol() const;
    unsigned short getPort() const;
    std::string getIp() const;
};

#endif //BOMBER_STUDENT_SOCKET_ADDRESS_H