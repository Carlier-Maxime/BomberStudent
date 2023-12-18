#include "MineBomb.h"
#include "../utils/Config.h"

MineBomb::MineBomb(Case &case_, Game &game, u_int16_t pos) : Bomb(case_, game, "mine", pos, 0) {}

bool MineBomb::get([[maybe_unused]] Player *player) {
    explode();
    return Bomb::get(player);
}

void MineBomb::explode() {
    Bomb::explode([](u_char){return Config::getMineBombDamage();});
}
