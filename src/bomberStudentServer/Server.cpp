#include "Server.h"
#include "../utils/Log.h"
#include "../utils/Config.h"
#include "../utils/ConstantMessages.h"
#include "../utils/Utils.h"
#include "../utils/BomberStudentExceptions.h"
#include <unistd.h>
#include <csignal>

Server::Server() : address(SocketAddress("::1",Config::getServerPort())), socketTCP(address.getProtocol()) {
    socketTCP.bind(address);
    socketTCP.listen(5);
}

Server::~Server() = default;

[[noreturn]] void Server::loopUDP() {
    Utils::processName= "Server:UDP";
    auto socketUDP = SocketUDP(address.getProtocol(), true);
    socketUDP.bind(address);
    SocketAddress client = SocketAddress("::", 0);
    for (;;) {
        Log::info("waiting client...");
        while (socketUDP.receive(&client)!=ConstantMessages::lookingServers);
        Log::info("client found !");
        socketUDP.send(ConstantMessages::serverHello, client);
    }
}

void Server::run() {
    int pid;
    if ((pid=fork())==-1) throw SystemException("fork failed");
    else if (pid==0) loopUDP();
    SocketAddress client = SocketAddress("::", 0);
    auto socket = socketTCP.accept();
    Log::info("client connected !");
    kill(pid,2);
}
