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
