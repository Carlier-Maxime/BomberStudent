#ifndef BOMBER_STUDENT_CONFIG_H
#define BOMBER_STUDENT_CONFIG_H


#include "../socket/SocketAddress.h"

class Config {
public:
    static Protocol getProtocol();
    static unsigned short getServerPort();
    static const std::string &getLogFilePath();
    static unsigned char getGameReadyTime();
private:
    static const Protocol protocol = Protocol::IPV6;
    static const unsigned short serverPort = 42069;
    static const std::string logFilePath;
    static const unsigned char gameReadyTime = 3;
};

#endif //BOMBER_STUDENT_CONFIG_H
