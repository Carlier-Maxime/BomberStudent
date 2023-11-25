#include "SocketAddress.h"

#include <utility>
#include "../utils/Config.h"

std::ostream &operator<<(std::ostream &os, const Protocol &protocol) {
    os << (protocol==Protocol::IPV4 ? "IPV4" : "IPV6");
    return os;
}

SocketAddress::SocketAddress(std::string ip, unsigned short port, Protocol protocol) : protocol(protocol), port(port), ip(std::move(ip)) {}

Protocol SocketAddress::getProtocol() const {
    return protocol;
}

unsigned short SocketAddress::getPort() const {
    return port;
}

std::string SocketAddress::getIp() const {
    return ip;
}

void SocketAddress::setProtocol(Protocol newProtocol) {
    protocol = newProtocol;
}

void SocketAddress::setPort(unsigned short newPort) {
    port = newPort;
}

void SocketAddress::setIp(const std::string &newIP) {
    ip = newIP;
}

std::ostream &operator<<(std::ostream &os, const SocketAddress &address) {
    os << "ip: " << address.ip << " port: " << address.port << " protocol: " << address.protocol;
    return os;
}

SocketAddress::SocketAddress(std::string ip, unsigned short port) : SocketAddress(std::move(ip), port, Config::getProtocol()) {}
