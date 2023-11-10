#include "Config.h"

Protocol Config::getProtocol() {
    return protocol;
}

unsigned short Config::getServerPort() {
    return serverPort;
}

unsigned short Config::getClientPort() {
    return clientPort;
}
