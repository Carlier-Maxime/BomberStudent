#include "Player.h"

#include <utility>
#include <sstream>

Player::Player(std::string name) : name(std::move(name)), life(100), speed(1), nbClassicBomb(2), nbMine(0),
nbRemoteBomb(1), impactDist(2), posX(0), posY(0), invincible(false) {}

std::string Player::toJSON() const {
    std::ostringstream json;
    json << R"({"name":")" << name << R"(","pos":")" << posY << "," << posX <<"\"}";
    return json.str();
}

std::string Player::toJSONState() const {
    std::ostringstream json;
    json << "{\"life\":"<< life <<",\"speed\":"<< speed <<",\"nbClassicBomb\":"<<nbClassicBomb
        <<",\"nbMine\":"<<nbMine<<",\"nbRemoteBomb\":"<<nbRemoteBomb<<",\"impactDist\":"
        <<impactDist<<",\"invincible\":"<<(invincible ? "True" : "False")<<"}";
    return json.str();
}

const std::string &Player::getName() const {
    return name;
}
