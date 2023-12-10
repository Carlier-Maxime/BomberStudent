#ifndef BOMBER_STUDENT_GAME_H
#define BOMBER_STUDENT_GAME_H


#include "Map.h"
#include "Player.h"
#include <shared_mutex>

class Game {
public:
    Game(std::string name, const Map &map);
    Game(const Game& other);
    Game& operator=(const Game& other);
    [[nodiscard]] std::string toJSON() const;
    [[nodiscard]] const std::string &getName() const;
    Player *newPlayer(const SocketTCP *socket);
    Map& getMap();
    std::string jsonCreateOrJoinGame(const Player& player);
    void removePlayer(const Player& player);
    bool isStarted() const;
    void start(const Player& player);
    void sendForAllPlayers(const std::string& msg) const;
    void sendForAllPlayersExcept(const std::string& msg, const Player& player_excluded) const;
    u_char getWidth();
    u_char getHeight();
private:
    mutable std::shared_mutex mutex;
    std::string name;
    Map map;
    std::vector<Player> players;
    bool started;
};


#endif //BOMBER_STUDENT_GAME_H
