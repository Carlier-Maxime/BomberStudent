#include "Server.h"
#include "Log.h"
#include "Config.h"
#include "ConstantMessages.h"

Server::Server() : socket(SocketAddress("::1",Config::getServerPort(),Config::getProtocol()), true) {}

Server::~Server() = default;

void Server::run() {
    SocketAddress address = SocketAddress("::", 0, Config::getProtocol());
    Log::info("waiting for client...");
    while (socket.receive(&address)!=ConstantMessages::lookingServers);
    socket.send(ConstantMessages::serverHello, address);
    Log::info("client found !");
}
