#ifndef BOMBER_STUDENT_GAME_H
#define BOMBER_STUDENT_GAME_H


#include "Map.h"
#include "Player.h"

class Game {
public:
    Game(std::string name, const Map &map);
    [[nodiscard]] std::string toJSON() const;
    [[nodiscard]] const std::string &getName() const;
    Player* newPlayer();
    bool isAccessiblePos(unsigned char x, unsigned char y);
    std::string jsonCreateOrJoinGame(const Player& player);
    void removePlayer(const Player& player);
private:
    std::mutex mutex;
    std::string name;
    Map map;
    std::vector<Player> players;
};


#endif //BOMBER_STUDENT_GAME_H
