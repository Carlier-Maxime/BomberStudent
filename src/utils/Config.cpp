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

float Config::getDefaultLife() {
    return defaultLife;
}

float Config::getDefaultSpeed() {
    return defaultSpeed;
}

float Config::getFreezeTime() {
    return freezeTime;
}

float Config::getBombMaxDamage() {
    return bombMaxDamage;
}

float Config::getBombDamageFactor() {
    return bombDamageFactor;
}

float Config::getMineBombDamage() {
    return mineBombDamage;
}

float Config::getInvincibleTime() {
    return invincibleTime;
}

float Config::getSpeedFactor() {
    return speedFactor;
}

float Config::getMaxLife() {
    return maxLife;
}

char Config::getMsgSeparator() {
    return msg_separator;
}
