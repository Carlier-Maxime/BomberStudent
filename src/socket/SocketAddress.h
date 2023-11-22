#ifndef BOMBER_STUDENT_SOCKET_ADDRESS_H
#define BOMBER_STUDENT_SOCKET_ADDRESS_H

#include <string>
#include <ostream>

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
    SocketAddress(std::string ip, unsigned short port);
    SocketAddress(std::string ip, unsigned short port, Protocol protocol);
    [[nodiscard]] Protocol getProtocol() const;
    [[nodiscard]] unsigned short getPort() const;
    [[nodiscard]] std::string getIp() const;
    void setProtocol(Protocol protocol);
    void setPort(unsigned short port);
    void setIp(const std::string &ip);

    friend std::ostream &operator<<(std::ostream &os, const SocketAddress &address);
};

#endif //BOMBER_STUDENT_SOCKET_ADDRESS_H