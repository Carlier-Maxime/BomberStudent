#include "Client.h"
#include "Log.h"
#include "Config.h"

Client::Client() : socket(SocketAddress("::1", Config::getClientPort(), Config::getProtocol()), true) {}

void Client::run() {
    SocketAddress multicast = SocketAddress("255.255.255.255", Config::getServerPort(), Config::getProtocol());
    SocketAddress server_addr = SocketAddress("::", 0, Config::getProtocol());
    Log::info("Search server...");
    do socket.send("looking for bomberstudent servers", multicast);
    while (socket.receive(&server_addr)!="hello i’m a bomberstudent server");
    Log::info("Server found !");
}

Client::~Client() = default;
