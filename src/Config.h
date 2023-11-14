#ifndef BOMBER_STUDENT_CONFIG_H
#define BOMBER_STUDENT_CONFIG_H


#include "SocketAddress.h"

class Config {
public:
    static Protocol getProtocol();
    static unsigned short getServerPort();
    static const std::string &getLogFilePath();

private:
    static const Protocol protocol = Protocol::IPV6;
    static const unsigned short serverPort = 42069;
    static const std::string logFilePath;
};

#endif //BOMBER_STUDENT_CONFIG_H
