#include "Server.h"

Server::Server() : socket(SocketAddress("::1",42069,Protocol::IPV6)) {}

Server::~Server() = default;

void Server::run() {
    SocketAddress address = SocketAddress("::1", 0, Protocol::IPV6);
    while (socket.receive(&address)!="looking for bomberstudent servers");
    socket.send("hello i’m a bomberstudent server", address);
}
