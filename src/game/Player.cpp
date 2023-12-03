#include "Player.h"

#include <sstream>
#include "../utils/Utils.h"
#include "Game.h"

const std::string Player::possibleNames[] = {
        "Anis",
        "Antoine",
        "Arthur",
        "Axel",
        "Benjamin",
        "Bernard",
        "Cameron",
        "Chaker",
        "Christ",
        "Cyrille",
        "Elliot",
        "Emeline",
        "Enzo",
        "Godwin",
        "Guillaume",
        "Hadrien",
        "Hana",
        "Hugo",
        "Ismael",
        "Ismail",
        "James",
        "Jean-Marie",
        "Leo",
        "Lucas",
        "Marc",
        "Mathias",
        "Maxime",
        "Nicolas",
        "Patrice",
        "Patrick",
        "Paul",
        "Pierre",
        "Rabah",
        "Rayane",
        "Remi",
        "Theo",
        "Thi",
        "Thomas",
        "Ugo",
        "Walid",
        "William",
        "Yann",
        "Youcef",
        "Zhaoyang"
};

std::string Player::randomNames() {
    return Player::possibleNames[Utils::getRandomNumber(0, 43)];
}

Player::Player(Game* game) : game(game), name(randomNames()), speed(1), life(100), nbClassicBomb(2), nbMine(0),
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

void Player::move(unsigned char x, unsigned char y) {
    if (game && !game->isAccessiblePos(x, y)) return;
    posY=y;
    posX=x;
}
