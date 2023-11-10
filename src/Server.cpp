#include "Server.h"
#include "Log.h"
#include "Config.h"

Server::Server() : socket(SocketAddress("::1",Config::getServerPort(),Config::getProtocol()), true) {}

Server::~Server() = default;

void Server::run() {
    SocketAddress address = SocketAddress("::", 0, Config::getProtocol());
    Log::info("waiting for client...");
    while (socket.receive(&address)!="looking for bomberstudent servers");
    socket.send("hello i’m a bomberstudent server", address);
    Log::info("client found !");
}
