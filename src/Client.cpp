#include "Client.h"
#include "Log.h"
#include "Config.h"
#include "ConstantMessages.h"

Client::Client() : socket(SocketAddress("::1", Config::getClientPort()), true) {}

void Client::run() {
    SocketAddress multicast = SocketAddress("255.255.255.255", Config::getServerPort());
    SocketAddress server_addr = SocketAddress("::", 0);
    Log::info("Search server...");
    do socket.send(ConstantMessages::lookingServers, multicast);
    while (socket.receive(&server_addr)!=ConstantMessages::serverHello);
    Log::info("Server found !");
}

Client::~Client() = default;
