#ifndef BOMBERSTUDENT_ITEM_H
#define BOMBERSTUDENT_ITEM_H


#include "Game.h"

class Player;
class Case;

class Item {
protected:
    Game& game;
    Case& case_;
public:
    Item(Game& game, Case& case_);
    virtual bool get(Player *player) = 0;
    virtual ~Item() = default;
};


#endif //BOMBERSTUDENT_ITEM_H
