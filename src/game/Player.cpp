#include "Player.h"

#include <sstream>
#include <thread>
#include "../utils/Utils.h"
#include "Game.h"
#include "../json/JSONMessage.h"
#include "../utils/ConstantMessages.h"
#include "../utils/Config.h"

using CM = ConstantMessages;

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
name(randomNames()+std::to_string(id++)), speed(Config::getDefaultSpeed()), life(Config::getDefaultLife()),
nbClassicBomb(Config::getDefaultNbClassicBomb()), nbMine(Config::getDefaultNbMineBomb()), nbRemoteBomb(Config::getDefaultNbRemoteBomb()),
impactDist(Config::getDefaultImpactDist()), posX(posX), posY(posY), invincible(false), timeLastMove(std::chrono::high_resolution_clock::now()) {}

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
    auto timeMove = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::duration<float>>( timeMove - timeLastMove).count() < (1/speed)) return false;
    if (!game->isStarted() || !game->getMap().getCase(x, y)->isAccessible()) return false;
    game->getMap().getCase(posX, posY)->resetAccessible();
    game->getMap().getCase(x, y)->toNoAccessible();
    posY=y;
    posX=x;
    timeLastMove = timeMove;
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

std::string Player::toJSONMove(const std::string &direction) const {
    std::ostringstream oss;
    oss << "POST player/position/update\n{\"player\":\"" << name << R"(","dir":")" << direction << "\"}";
    return oss.str();
}

bool Player::poseBomb(const std::string &type) {
    if (!game->getMap().getCase(posX,posY)) return false;
    if (type=="classic" && nbClassicBomb>0) {
        nbClassicBomb--;
        std::thread th([x=posX, y=posY]() {
            std::this_thread::sleep_for(std::chrono::seconds(Config::getDetonationTime()));
        });
        th.detach();
    } else if (type=="remote" && nbRemoteBomb>0) {
        nbRemoteBomb--;
        std::thread th([]() {});
        th.detach();
    } else if (type=="mine" && nbMine>0) {
        nbMine--;
        std::thread th([]() {});
        th.detach();
    } else return false;
    return true;
}

std::string Player::toJSONAttackBomb() const {
    std::ostringstream oss, msg;
    oss << "\"player\":" << toJSONState();
    msg << "bomb is armed at pos " << std::to_string(posX) << ',' << std::to_string(posY);
    return JSONMessage::actionMessage("attack/bomb",201,msg.str(), oss.str());
}

std::string Player::toJSONAttackNewBomb(const std::string &type) const {
    std::ostringstream json;
    json << CM::postAttackNewBomb << "\n{\"pos\":\""<< posX << ","<< posY << R"(","type":")"<< type <<"\"}";
    return json.str();
}
