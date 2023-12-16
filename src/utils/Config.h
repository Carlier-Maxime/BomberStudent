#ifndef BOMBER_STUDENT_CONFIG_H
#define BOMBER_STUDENT_CONFIG_H


#include "../socket/SocketAddress.h"

class Config {
public:
    static Protocol getProtocol();
    static unsigned short getServerPort();
    static const std::string &getLogFilePath();
    static unsigned char getGameReadyTime();
    static unsigned char getDetonationTime();
    static unsigned char getMinImpactDist();
    static unsigned char getMaxImpactDist();
    static unsigned char getDefaultImpactDist();
    static unsigned char getDefaultNbClassicBomb();
    static unsigned char getDefaultNbRemoteBomb();
    static unsigned char getDefaultNbMineBomb();
    static float getDefaultLife();
    static float getDefaultSpeed();
    static float getFreezeTime();

private:
    static const Protocol protocol = Protocol::IPV6;
    static const unsigned short serverPort = 42069;
    static const std::string logFilePath;
    static const unsigned char gameReadyTime = 3;
    static const unsigned char detonationTime = 4;
    static const unsigned char minImpactDist = 1;
    static const unsigned char maxImpactDist = 4;
    static const unsigned char defaultImpactDist = 2;
    static const unsigned char defaultNbClassicBomb = 2;
    static const unsigned char defaultNbRemoteBomb = 1;
    static const unsigned char defaultNbMineBomb = 0;
    constexpr static const float defaultLife = 100;
    constexpr static const float defaultSpeed = 4;
    constexpr static const float freezeTime = 1;
};

#endif //BOMBER_STUDENT_CONFIG_H
