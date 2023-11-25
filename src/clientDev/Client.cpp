#include "Client.h"
#include "../utils/Log.h"
#include "../utils/Config.h"
#include "../utils/ConstantMessages.h"
#include "../utils/BomberStudentExceptions.h"

Client::Client() : socketUDP(Config::getProtocol(), true), socketTCP(Config::getProtocol()) {}

void Client::run() {
    SocketAddress multicast = SocketAddress("255.255.255.255", Config::getServerPort());
    SocketAddress server_addr = SocketAddress("::", 0);
    socketUDP.setTimeout(3,0);
    Log::info("Search server...");
    search_server:
    try {
        do socketUDP.send(ConstantMessages::lookingServers, multicast);
        while (socketUDP.receive(&server_addr)!=ConstantMessages::serverHello);
    } catch (SocketException& e) {
        if (errno==EAGAIN || errno==EWOULDBLOCK) goto search_server;
        throw e;
    }
    Log::info("Server found !");
    socketTCP.connect(server_addr);
    Log::info("connected to the server");
}

Client::~Client() = default;
