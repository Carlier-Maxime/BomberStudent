#ifndef BOMBER_STUDENT_CONFIG_H
#define BOMBER_STUDENT_CONFIG_H


#include "SocketAddress.h"

class Config {
public:
    static Protocol getProtocol();
    static unsigned short getServerPort();
    static unsigned short getClientPort();
private:
    static const Protocol protocol = Protocol::IPV6;
    static const unsigned short serverPort = 42069;
    static const unsigned short clientPort = 40469;
};


#endif //BOMBER_STUDENT_CONFIG_H
