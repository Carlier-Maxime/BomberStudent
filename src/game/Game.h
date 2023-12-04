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
    static std::string gameCreationJSON(const Player& player, unsigned int mapId);
    std::string gameJoinJSON(const Player& player);
private:
    std::string name;
    Map map;
    std::vector<Player> players;
};


#endif //BOMBER_STUDENT_GAME_H
