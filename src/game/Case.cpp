#include "Case.h"

Case::Case() : player(nullptr) {}

void Case::setPlayer(Player *player) {
    Case::player = player;
}

Case *Case::explode([[maybe_unused]] unsigned char &impactDist) {
    if (player) player->takeDamage(impactDist==1 ? 20 : impactDist==2 ? 15 : impactDist==3 ? 12 : impactDist==4 ? 10 : 5);
    return nullptr;
}

