#include "Case.h"
#include "Item.h"

Case::Case() : game(nullptr), player(nullptr), item(nullptr) {}

void Case::setPlayer(Player *player) {
    Case::player = player;
}

Case *Case::explode([[maybe_unused]] unsigned char &impactDist, float damage) {
    if (player) player->takeDamage(damage);
    return nullptr;
}

Item* Case::getItem() {
    auto tmp = item;
    if (item) item=nullptr;
    return tmp;
}

void Case::setItem(Item *item) {
    Case::item = item;
}

Case::~Case() {
    delete item;
}

void Case::setGame(Game *game) {
    Case::game = game;
}

Game *Case::getGame() const {
    return game;
}
