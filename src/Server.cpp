#include "Server.h"
#include "Log.h"
#include "Config.h"
#include "ConstantMessages.h"

Server::Server() : address(SocketAddress("::1",Config::getServerPort())), socketUDP(address.getProtocol(), true), socketTCP(address.getProtocol()) {
    socketUDP.bind(address);
    socketTCP.bind(address);
    socketTCP.listen(5);
}

Server::~Server() = default;

void Server::run() {
    SocketAddress client = SocketAddress("::", 0);
    Log::info("waiting for client...");
    while (socketUDP.receive(&client)!=ConstantMessages::lookingServers);
    socketUDP.send(ConstantMessages::serverHello, client);
    Log::info("client found !");
    socketTCP.accept();
    Log::info("client connected !");
}
