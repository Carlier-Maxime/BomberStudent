#include "MineBomb.h"

MineBomb::MineBomb(Case &case_, Game &game, u_int16_t pos) : Bomb(case_, game, "mine", pos, 0) {}

bool MineBomb::get([[maybe_unused]] const Player *player) {
    explode();
    return Bomb::get(player);
}

void MineBomb::explode() {
    Bomb::explode([](u_char){return 30.f;});
}
