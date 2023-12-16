#include "Case.h"

Case::Case() : player(nullptr) {}

void Case::setPlayer(Player *player) {
    Case::player = player;
}

Case *Case::explode([[maybe_unused]] unsigned char &impactDist, float damage) {
    if (player) player->takeDamage(damage);
    return nullptr;
}

