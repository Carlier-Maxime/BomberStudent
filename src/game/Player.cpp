#include "Player.h"

#include <sstream>
#include "../utils/Utils.h"
#include "Game.h"

u_int Player::id = 0;

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

Player::Player(const SocketTCP* socket, Game* game, u_char posX, u_char posY) : socket(socket), game(game),
name(randomNames()+std::to_string(id++)), speed(1), life(100), nbClassicBomb(2), nbMine(0),
nbRemoteBomb(1), impactDist(2), posX(posX), posY(posY), invincible(false) {}

std::string Player::toJSON() const {
    std::ostringstream json;
    json << R"({"name":")" << name << R"(","pos":")" << posY << "," << posX <<"\"}";
    return json.str();
}

std::string Player::toJSONState() const {
    std::ostringstream json;
    json << "{\"life\":"<<std::to_string(life)<<",\"speed\":"<<speed<<",\"nbClassicBomb\":"<<std::to_string(nbClassicBomb)
        <<",\"nbMine\":"<<std::to_string(nbMine)<<",\"nbRemoteBomb\":"<<std::to_string(nbRemoteBomb)<<",\"impactDist\":"
        <<std::to_string(impactDist)<<",\"invincible\":"<<(invincible ? "true" : "false")<<"}";
    return json.str();
}

const std::string &Player::getName() const {
    return name;
}

bool Player::move(unsigned char x, unsigned char y) {
    if (!game->isStarted() || !game->getMap().getCase(x, y)->isAccessible()) return false;
    game->getMap().getCase(posX, posY)->resetAccessible();
    game->getMap().getCase(x, y)->toNoAccessible();
    posY=y;
    posX=x;
    return true;
}

u_int16_t Player::getPos() const {
    return MERGE_POS(posX, posY);
}

const SocketTCP* Player::getSocket() const {
    return socket;
}

bool Player::move(const std::string& direction) {
    u_char w = game->getMap().getWidth(), h = game->getMap().getHeight();
    u_char x = posX, y = posY;
    if (direction=="up") y = (y==0) ? h-1 : y-1;
    else if (direction=="down") y = (y==h-1) ? 0 : y+1;
    else if (direction=="left") x = (x==0) ? w-1 : x-1;
    else if (direction=="right") x = (x==w-1) ? 0 : x+1;
    else return false;
    return move(x,y);
}

std::string Player::toJSONMove(const std::string &direction) {
    std::ostringstream oss;
    oss << "POST player/position/update\n{\"player\":\"" << name << R"(","dir":")" << direction << "\"}";
    return oss.str();
}
