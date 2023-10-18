#include "SocketAddress.h"

SocketAddress::SocketAddress(std::string ip, unsigned short port, Protocol protocol) : ip(std::move(ip)), port(port), protocol(protocol) {}

Protocol SocketAddress::getProtocol() {
    return protocol;
}

unsigned short SocketAddress::getPort() {
    return port;
}

std::string SocketAddress::getIp() {
    return ip;
}