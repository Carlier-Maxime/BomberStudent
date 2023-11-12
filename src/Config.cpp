#include "Config.h"

const std::string Config::logFilePath = "log.txt";

Protocol Config::getProtocol() {
    return protocol;
}

unsigned short Config::getServerPort() {
    return serverPort;
}

unsigned short Config::getClientPort() {
    return clientPort;
}

const std::string &Config::getLogFilePath() {
    return logFilePath;
}
