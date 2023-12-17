#ifndef BOMBERSTUDENT_MINEBOMB_H
#define BOMBERSTUDENT_MINEBOMB_H


#include "Bomb.h"

class MineBomb : public Bomb {
public:
    MineBomb(Case &case_, Game &game, u_int16_t pos);

    bool get(const Player *player) override;

    void explode() override;
};


#endif //BOMBERSTUDENT_MINEBOMB_H
