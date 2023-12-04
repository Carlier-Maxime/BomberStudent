#ifndef BOMBER_STUDENT_GAMEMANAGER_H
#define BOMBER_STUDENT_GAMEMANAGER_H


#include <vector>
#include "Game.h"

class GameManager {
private:
    static GameManager instance;
    std::vector<Game> games;
    GameManager();
public:
    static GameManager* getInstance();
    std::string toJSON();
    bool isExist(const std::string& name);
    Game* addGame(const std::string& name, const Map& map);
    Game* getGame(const std::string& name);
    void removeGame(const std::string& name);
};


#endif //BOMBER_STUDENT_GAMEMANAGER_H
