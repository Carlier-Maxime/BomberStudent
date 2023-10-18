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
    Protocol getProtocol();
    unsigned short getPort();
    std::string getIp();
};

#endif //BOMBER_STUDENT_SOCKET_ADDRESS_H