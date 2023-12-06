#include "Server.h"
#include "../utils/Log.h"
#include "../utils/Config.h"
#include "../utils/BomberStudentExceptions.h"
#include "../utils/Utils.h"
#include "../utils/ConstantMessages.h"
#include "../game/MapManager.h"
#include "../game/GameManager.h"
#include <sys/wait.h>

using CM = ConstantMessages;

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
                threads.emplace_back(&Server::handleClient, clients.back());
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

void Server::handleClient(const SocketTCP* socket) {
    if (!socket) return;
    Utils::threadName = "handlingClient";
    Player* player = nullptr;
    Game* game = nullptr;
    try {
        for (;;) {
            try {
                std::string msg = socket->receive();
                if (msg.empty()) {
                    Log::info("Client disconnected : " + socket->getAddress().toString());
                    break;
                }else if (msg==CM::getMapList) socket->send(MapManager::getInstance()->toJSON());
                else if (msg==CM::getGameList) socket->send(GameManager::getInstance()->toJSON());
                else if (msg.compare(0, CM::postGameCreate.size(), CM::postGameCreate)==0)
                    handleGameCreate(socket, json::parse(msg.substr(CM::postGameCreate.size())), player,game);
                else if (msg.compare(0, CM::postGameJoin.size(), CM::postGameJoin)==0)
                    handleGameJoin(socket, json::parse(msg.substr(CM::postGameJoin.size())), player,game);
                else if (msg==CM::postGameStart && game && player) game->start(*player);
                else {
                    Log::warning("Unknown request : "+msg);
                    socket->send(CM::badRequest);
                }
            } catch (SocketException& e) {
                if (errno==EINTR) break;
                throw e;
            }
        }
    } catch (std::exception& e) {
        Log::error(e.what());
        Log::warning("terminated abnormally communication with client : "+socket->getAddress().toString());
    }
    if (player && game) game->removePlayer(*player);
    Log::info("terminate");
}

void Server::handleGameCreate(const SocketTCP *socket, json data, Player *&player, Game *&game) {
    std::string name = data["name"];
    int id = data["mapId"];
    try {
        if (player && game) game->removePlayer(*player);
        game = GameManager::getInstance()->addGame(name, MapManager::getInstance()->get(id));
        if (!game) socket->send(CM::failedCreateGame);
        player = game->newPlayer(socket);
        if (!player) socket->send(CM::failedCreateGame);
        socket->send(game->jsonCreateOrJoinGame(*player));
    } catch (std::exception& e) {
        Log::warning(e.what());
        socket->send(CM::failedCreateGame);
    }
}

void Server::handleGameJoin(const SocketTCP *socket, json data, Player *&player, Game *&game) {
    std::string name = data["name"];
    try {
        if (player && game) game->removePlayer(*player);
        game = GameManager::getInstance()->getGame(name);
        if (!game) socket->send(CM::failedJoinGame);
        player = game->newPlayer(socket);
        if (!player) socket->send(CM::failedJoinGame);
        socket->send(game->jsonCreateOrJoinGame(*player));
    } catch (std::exception& e) {
        Log::warning(e.what());
        socket->send(CM::failedJoinGame);
    }
}

void Server::handleUDP() {
    Utils::threadName= "handlingUDP";
    Log::info("start UDP handler");
    SocketAddress client = SocketAddress("::", 0);
    for (;;) {
        try {
            while (socketUDP.receive(&client)!=CM::lookingServers);
        } catch (SocketException& e) {
            if (errno==EINTR) break;
            throw e;
        }
        Log::info("client found - "+client.toString());
        socketUDP.send(CM::serverHello, client);
    }
    Log::info("stopped");
}
