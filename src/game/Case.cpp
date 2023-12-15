#include "Case.h"

Case::Case() : player(nullptr) {}

void Case::setPlayer(Player *player) {
    Case::player = player;
}

Case *Case::explode([[maybe_unused]] unsigned char &impactDist) {
    if (player) player->takeDamage(20);
    return nullptr;
}

