#include "Server.h"
#include "../utils/Log.h"
#include "../utils/Config.h"
#include "../utils/BomberStudentExceptions.h"
#include "../utils/Utils.h"
#include <unistd.h>
#include <sys/wait.h>

Server::Server() : address(SocketAddress("::1",Config::getServerPort())), socketTCP(address.getProtocol()), clients(), threads() {
    socketTCP.bind(address);
    socketTCP.listen(5);
}

Server::~Server() {
    for (auto* socket : clients) delete socket;
}

void Server::run() {
    int pid;
    if ((pid=fork())==-1) throw SystemException("Launching handler UDP failed (fork)");
    else if (pid==0) {
        char* args[] = {(char*) "./handlerUDP", nullptr};
        execv(args[0], args);
        throw SystemException("Launching handler UDP failed (exec)");
    }
    const struct sigaction act = {
            {[](int){}},
            {},
            0,
            {}
    };
    sigaction(SIGINT, &act, nullptr);
    try {
        for (;;) {
            try {
                clients.push_back(socketTCP.accept());
                Log::info("Client connected - " + clients.back()->getAddress().toString());
                threads.emplace_back(&Server::handleClient, this, *clients.back());
            } catch (SocketException& e) {
                if (errno==EINTR) break;
                throw e;
            }
        }
    } catch (std::exception& e) {
        Log::error(e.what());
        Log::warning("shutdown server");
    }
    kill(pid,SIGINT);
    waitpid(pid, nullptr, 0);
    for (auto & thread : threads) pthread_kill(thread.native_handle(), SIGINT);
    for (auto & thread : threads) thread.join();
}

void Server::handleClient(const SocketTCP& socket) {
    Utils::threadName = "handlingClient";
    try {
        for (;;) {
            try {
                std::string msg = socket.receive();
                if (msg.empty()) break;
                Log::info("A new message : "+msg);
            } catch (SocketException& e) {
                if (errno==EINTR) break;
                throw e;
            }
        }
    } catch (std::exception& e) {
        Log::error(e.what());
        Log::warning("terminated abnormally");
    }
    Log::info("terminate");
}
