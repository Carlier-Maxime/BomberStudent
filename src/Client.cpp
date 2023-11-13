#include "Client.h"
#include "Log.h"
#include "Config.h"
#include "ConstantMessages.h"

Client::Client() : address(SocketAddress("::1", Config::getClientPort())), socketUDP(address, true), socketTCP(address, false) {}

void Client::run() {
    SocketAddress multicast = SocketAddress("255.255.255.255", Config::getServerPort());
    SocketAddress server_addr = SocketAddress("::", 0);
    Log::info("Search server...");
    do socketUDP.send(ConstantMessages::lookingServers, multicast);
    while (socketUDP.receive(&server_addr)!=ConstantMessages::serverHello);
    Log::info("Server found !");
    socketTCP.connect(server_addr);
    Log::info("connected to the server");
}

Client::~Client() = default;
