#include "Case.h"

Case::Case() : player(nullptr) {}

Player *Case::getPlayer() const {
    return player;
}

void Case::setPlayer(Player *player) {
    Case::player = player;
}
