#include <sys/socket.h>
#include "SocketUDP.h"

SocketUDP::SocketUDP(Protocol protocol) : Socket(protocol, SOCK_DGRAM, false) {}

SocketUDP::SocketUDP(Protocol protocol, bool enableBroadcast) : Socket(protocol, SOCK_DGRAM, enableBroadcast) {}
