#include "Game.h"
#include "../utils/Utils.h"

#include <utility>
#include <sstream>

Game::Game(std::string name, const Map &map) : name(std::move(name)), map(map), players() {}

std::string Game::toJSON() const{
    std::ostringstream json;
    json << R"({"name":")" << name << R"(","nbPlayer":)"<< players.size() << ",\"mapId\":" << map.getId() << "}";
    return json.str();
}

const std::string &Game::getName() const {
    return name;
}

Player* Game::newPlayer() {
    players.emplace_back(this);
    u_int16_t pos = map.getRandomAvailablePos();
    u_char x, y;
    SPLIT_POS(pos,x,y);
    Player* player = &(*players.end());
    player->move(x,y);
    return player;
}

bool Game::isAccessiblePos(unsigned char x, unsigned char y) {
    return map.isAccessiblePos(x, y);
}
