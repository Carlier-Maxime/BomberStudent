#include "Config.h"

const std::string Config::logFilePath = "log.txt";

Protocol Config::getProtocol() {
    return protocol;
}

unsigned short Config::getServerPort() {
    return serverPort;
}

const std::string &Config::getLogFilePath() {
    return logFilePath;
}

unsigned char Config::getGameReadyTime() {
    return gameReadyTime;
}

unsigned char Config::getDetonationTime() {
    return detonationTime;
}

unsigned char Config::getMinImpactDist() {
    return minImpactDist;
}

unsigned char Config::getMaxImpactDist() {
    return maxImpactDist;
}

unsigned char Config::getDefaultImpactDist() {
    return defaultImpactDist;
}

unsigned char Config::getDefaultNbClassicBomb() {
    return defaultNbClassicBomb;
}

unsigned char Config::getDefaultNbRemoteBomb() {
    return defaultNbRemoteBomb;
}

unsigned char Config::getDefaultNbMineBomb() {
    return defaultNbMineBomb;
}

unsigned char Config::getDefaultLife() {
    return defaultLife;
}

float Config::getDefaultSpeed() {
    return defaultSpeed;
}

float Config::getFreezeTime() {
    return freezeTime;
}
