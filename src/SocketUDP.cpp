#include <bits/socket_type.h>
#include "SocketUDP.h"

SocketUDP::SocketUDP(const SocketAddress &address) : Socket(address, SOCK_DGRAM, false) {}

SocketUDP::SocketUDP(const SocketAddress &address, bool enableBroadcast) : Socket(address, SOCK_DGRAM, enableBroadcast) {}
