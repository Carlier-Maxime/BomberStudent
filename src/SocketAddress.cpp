#include "SocketAddress.h"

SocketAddress::SocketAddress(std::string ip, unsigned short port, Protocol protocol) : protocol(protocol), port(port), ip(std::move(ip)) {}

Protocol SocketAddress::getProtocol() {
    return protocol;
}

unsigned short SocketAddress::getPort() const {
    return port;
}

std::string SocketAddress::getIp() {
    return ip;
}