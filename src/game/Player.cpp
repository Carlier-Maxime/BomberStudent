#include "Player.h"

#include <utility>
#include <sstream>

Player::Player(std::string name) : name(std::move(name)), speed(1), life(100), nbClassicBomb(2), nbMine(0),
nbRemoteBomb(1), impactDist(2), posX(0), posY(0), invincible(false) {}

std::string Player::toJSON() const {
    std::ostringstream json;
    json << R"({"name":")" << name << R"(","pos":")" << posY << "," << posX <<"\"}";
    return json.str();
}

std::string Player::toJSONState() const {
    std::ostringstream json;
    json << "{\"life\":"<<std::to_string(life)<<",\"speed\":"<<speed<<",\"nbClassicBomb\":"<<std::to_string(nbClassicBomb)
        <<",\"nbMine\":"<<std::to_string(nbMine)<<",\"nbRemoteBomb\":"<<std::to_string(nbRemoteBomb)<<",\"impactDist\":"
        <<std::to_string(impactDist)<<",\"invincible\":"<<(invincible ? "True" : "False")<<"}";
    return json.str();
}

const std::string &Player::getName() const {
    return name;
}
