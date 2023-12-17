#ifndef BOMBERSTUDENT_REMOTE_BOMB_H
#define BOMBERSTUDENT_REMOTE_BOMB_H


#include "Bomb.h"

class RemoteBomb : public Bomb {
public:
    RemoteBomb(Case& case_, Game& game, u_int16_t pos, u_char impactDist);
};

#endif //BOMBERSTUDENT_REMOTE_BOMB_H
