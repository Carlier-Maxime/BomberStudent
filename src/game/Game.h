#ifndef BOMBER_STUDENT_GAME_H
#define BOMBER_STUDENT_GAME_H


#include "Map.h"
#include "Player.h"

class Game {
public:
    Game(std::string name, const Map &map);
    [[nodiscard]] std::string toJSON() const;
    [[nodiscard]] const std::string &getName() const;
    void addPlayer(const Player& player);
private:
    std::string name;
    Map map;
    std::vector<Player> players;
};


#endif //BOMBER_STUDENT_GAME_H
