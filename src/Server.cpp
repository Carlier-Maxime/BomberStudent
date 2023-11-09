#include "Server.h"
#include "Log.h"

Server::Server() : socket(SocketAddress("::1",42069,Protocol::IPV6), true) {}

Server::~Server() = default;

void Server::run() {
    SocketAddress address = SocketAddress("::", 0, Protocol::IPV6);
    Log::info("waiting for client...");
    while (socket.receive(&address)!="looking for bomberstudent servers");
    socket.send("hello i’m a bomberstudent server", address);
    Log::info("client found !");
}
