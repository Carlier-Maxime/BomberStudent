#include "Server.h"
#include "../utils/Log.h"
#include "../utils/Config.h"
#include "../utils/BomberStudentExceptions.h"
#include <unistd.h>
#include <sys/wait.h>

Server::Server() : address(SocketAddress("::1",Config::getServerPort())), socketTCP(address.getProtocol()) {
    socketTCP.bind(address);
    socketTCP.listen(5);
}

Server::~Server() = default;

void Server::run() {
    int pid;
    if ((pid=fork())==-1) throw SystemException("Launching handler UDP failed (fork)");
    else if (pid==0) {
        char* args[] = {(char*) "./handlerUDP", nullptr};
        execv(args[0], args);
        throw SystemException("Launching handler UDP failed (exec)");
    }
    SocketAddress client = SocketAddress("::", 0);
    auto socket = socketTCP.accept();
    Log::info("client connected !");
    kill(pid,2);
    waitpid(pid, nullptr, 0);
}
