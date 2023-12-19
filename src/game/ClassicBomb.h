#ifndef BOMBERSTUDENT_CLASSICBOMB_H
#define BOMBERSTUDENT_CLASSICBOMB_H


#include "Bomb.h"

class ClassicBomb : public Bomb {
private:
    std::thread* th;
public:
    ClassicBomb(Case& case_, Game& game, u_int16_t pos, u_char impactDist);
    void explode() override;

    ~ClassicBomb() override;
};


#endif //BOMBERSTUDENT_CLASSICBOMB_H
