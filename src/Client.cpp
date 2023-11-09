#include "Client.h"
#include "Log.h"

Client::Client() : socket(SocketAddress("::1", 40469, Protocol::IPV6), true) {}

void Client::run() {
    SocketAddress multicast = SocketAddress("255.255.255.255", 42069, Protocol::IPV6);
    SocketAddress server_addr = SocketAddress("::1", 42069, Protocol::IPV6);
    Log::info("Search server...");
    do socket.send("looking for bomberstudent servers", multicast);
    while (socket.receive(&server_addr)!="hello i’m a bomberstudent server");
    Log::info("Server found !");
}

Client::~Client() = default;
