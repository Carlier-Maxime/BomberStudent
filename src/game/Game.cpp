#include "Game.h"

#include <utility>
#include <sstream>

Game::Game(std::string name, const Map &map) : name(std::move(name)), map(map), players() {}

std::string Game::toJSON() const{
    std::ostringstream json;
    json << R"({"name":")" << name << R"(","nbPlayer":)"<< players.size() << ",\"mapId\":" << map.getId() << "}";
    return json.str();
}