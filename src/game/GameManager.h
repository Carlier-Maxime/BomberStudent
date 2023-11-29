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
};


#endif //BOMBER_STUDENT_GAMEMANAGER_H
