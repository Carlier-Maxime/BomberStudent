#ifndef BOMBERSTUDENT_BOMB_H
#define BOMBERSTUDENT_BOMB_H

#include <string>
#include "Item.h"

class Game;

class Bomb : public Item {
private:
    Game& game;
    std::string type;
    u_int16_t pos;
    u_char impactDist;
    bool exploded;
public:
    Bomb(Case& case_, Game& game, std::string type, u_int16_t pos, u_char impactDist);
    static float damage(u_char distOfImpact);
    bool get(const Player *player) override;
    virtual void explode();
    ~Bomb() override;
};

#endif //BOMBERSTUDENT_BOMB_H
