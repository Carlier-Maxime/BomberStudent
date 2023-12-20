#include "SocketAddress.h"

#include <utility>
#include <sstream>
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
    os << "IP: " << address.ip << ", Port: " << address.port << ", Protocol: " << address.protocol;
    return os;
}

SocketAddress::SocketAddress(std::string ip, unsigned short port) : SocketAddress(std::move(ip), port, Config::getProtocol()) {}

std::string SocketAddress::toString() const {
    std::ostringstream oss;
    oss << *this;
    return std::string(oss.str());
}

SocketAddress::SocketAddress(unsigned short port) : SocketAddress(getIPLoopBack(), port, Config::getProtocol()) {}

std::string SocketAddress::getIPLoopBack() {
    return Config::getProtocol()==Protocol::IPV6 ? "::1" : "127.0.0.1";
}

SocketAddress::SocketAddress() : SocketAddress(getIPLoopBack(), 0, Config::getProtocol()) {}
