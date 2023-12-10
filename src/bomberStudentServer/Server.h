#ifndef BOMBER_STUDENT_SERVER_H
#define BOMBER_STUDENT_SERVER_H


#include <vector>
#include <thread>
#include <nlohmann/json.hpp>
#include "../socket/SocketUDP.h"
#include "../socket/SocketTCP.h"
#include "../game/Player.h"

using json = nlohmann::json;

class Server {
private:
    SocketAddress address;
    SocketUDP socketUDP;
    SocketTCP socketTCP;
    std::vector<SocketTCP*> clients;
    std::vector<std::thread> threads;
    void handleUDP();
    static void handleClient(const SocketTCP* socket);
    static void processClientMessages(const SocketTCP *socket, const std::string &msg_received, Player *&player, Game *&game);
    static void handleGameCreate(const SocketTCP *socket, const json& data, Player *&player, Game *&game);
    static void handleGameJoin(const SocketTCP *socket, const json& data, Player *&player, Game *&game);
    static void handlePlayerMove(const json &data, Player *player, const Game *game);
    static void handleAttackBomb(const json &data, Player *player, Game *game);
public:
    Server();
    ~Server();
    void run();
};


#endif //BOMBER_STUDENT_SERVER_H
