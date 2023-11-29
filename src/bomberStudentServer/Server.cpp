#include "Server.h"
#include "../utils/Log.h"
#include "../utils/Config.h"
#include "../utils/BomberStudentExceptions.h"
#include "../utils/Utils.h"
#include "../utils/ConstantMessages.h"
#include "../game/MapManager.h"
#include "../game/GameManager.h"
#include <sys/wait.h>

Server::Server() : address(SocketAddress("::1",Config::getServerPort())), socketUDP(address.getProtocol(), true), socketTCP(address.getProtocol()), clients(), threads() {
    socketUDP.bind(address);
    socketTCP.bind(address);
    socketTCP.listen(5);
}

Server::~Server() {
    for (auto* socket : clients) delete socket;
}

void Server::run() {
    const struct sigaction act = {
            {[](int){}},
            {},
            0,
            {}
    };
    sigaction(SIGINT, &act, nullptr);
    threads.emplace_back(&Server::handleUDP, this);
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
    for (auto & thread : threads) pthread_kill(thread.native_handle(), SIGINT);
    for (auto & thread : threads) thread.join();
}

void Server::handleClient(const SocketTCP& socket) {
    Utils::threadName = "handlingClient";
    try {
        for (;;) {
            try {
                std::string msg = socket.receive();
                if (msg.empty()) {
                    Log::info("Client disconnected : " + socket.getAddress().toString());
                    break;
                } else if (msg==ConstantMessages::getMapList) {
                    socket.send(MapManager::getInstance()->toJSON());
                } else if (msg==ConstantMessages::getGameList) {
                    socket.send(GameManager::getInstance()->toJSON());
                } else if (msg.compare(0, ConstantMessages::postGameCreate.size(), ConstantMessages::postGameCreate)==0) {
                    Log::warning("request not implemented : "+msg);
                    socket.send(ConstantMessages::badRequest);
                } else {
                    Log::warning("Unknown request : "+msg);
                    socket.send(ConstantMessages::badRequest);
                }
            } catch (SocketException& e) {
                if (errno==EINTR) break;
                throw e;
            }
        }
    } catch (std::exception& e) {
        Log::error(e.what());
        Log::warning("terminated abnormally communication with client : "+socket.getAddress().toString());
    }
    Log::info("terminate");
}

void Server::handleUDP() {
    Utils::threadName= "handlingUDP";
    Log::info("start UDP handler");
    SocketAddress client = SocketAddress("::", 0);
    for (;;) {
        try {
            while (socketUDP.receive(&client)!=ConstantMessages::lookingServers);
        } catch (SocketException& e) {
            if (errno==EINTR) break;
            throw e;
        }
        Log::info("client found - "+client.toString());
        socketUDP.send(ConstantMessages::serverHello, client);
    }
    Log::info("stopped");
}
