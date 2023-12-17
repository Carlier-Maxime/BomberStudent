#include "Player.h"

#include <sstream>
#include <thread>
#include "../utils/Utils.h"
#include "Game.h"
#include "../json/JSONMessage.h"
#include "../utils/ConstantMessages.h"
#include "../utils/Config.h"
#include "Bomb.h"
#include "../utils/Log.h"
#include "RemoteBomb.h"
#include "ClassicBomb.h"
#include "MineBomb.h"

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
impactDist(Config::getDefaultImpactDist()), posX(posX), posY(posY),
timeLastMove(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())),
timeInvincible(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())) {}

std::string Player::toJSON() const {
    std::ostringstream json;
    json << R"({"name":")" << name << R"(","pos":")" << posY << "," << posX <<"\"}";
    return json.str();
}

std::string Player::toJSONState() const {
    std::ostringstream json;
    json << "{\"life\":"<<life<<",\"speed\":"<<speed<<",\"nbClassicBomb\":"<<std::to_string(nbClassicBomb)
        <<",\"nbMine\":"<<std::to_string(nbMine)<<",\"nbRemoteBomb\":"<<std::to_string(nbRemoteBomb)<<",\"impactDist\":"
        <<std::to_string(impactDist)<<",\"invincible\":"<<(isInvincible() ? "true" : "false")<<"}";
    return json.str();
}

const std::string &Player::getName() const {
    return name;
}

bool Player::move(unsigned char x, unsigned char y) {
    auto timeMove = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    if (std::chrono::duration<float>(timeMove - timeLastMove).count() < (1/speed)) return false;
    if (!game->isStarted() || !game->getMap().getCase(x, y)->isAccessible()) return false;
    auto* item = game->getMap().getCase(x, y)->getItem();
    if (item && !item->get(this)) return false;
    game->getMap().getCase(posX, posY)->setPlayer(nullptr);
    game->getMap().getCase(posX, posY)->resetAccessible();
    game->getMap().getCase(x, y)->toNoAccessible();
    game->getMap().getCase(x, y)->setPlayer(this);
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
    auto* case_ = game->getMap().getCase(posX,posY);
    Bomb* bomb;
    if (!case_ || case_->getItem()) return false;
    u_int16_t pos = MERGE_POS(posX, posY);
    if (type=="classic" && nbClassicBomb>0) {
        nbClassicBomb--;
        bomb = new ClassicBomb(*case_, *game, pos, impactDist);
        bomb->explode();
    } else if (type=="remote" && nbRemoteBomb>0) {
        nbRemoteBomb--;
        bomb = new RemoteBomb(*case_, *game, pos, impactDist);
        remoteBombs.emplace_back(pos);
    } else if (type=="mine" && nbMine>0) {
        nbMine--;
        bomb = new MineBomb(*case_, *game, pos);
    } else return false;
    case_->setItem(bomb);
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

void Player::takeDamage(float damage) {
    if (isInvincible()) return;
    life = (life < damage) ? 0 : life-damage;
    timeLastMove = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    timeLastMove += std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::duration<float>(Config::getFreezeTime() - 1/speed)));
    timeInvincible = timeLastMove;
    socket->send(CM::postAttackAffect+toJSONState());
}

bool Player::isInvincible() const {
    return timeInvincible > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void Player::explodeRemoteBombs() {
    u_char x, y;
    for (auto pos : remoteBombs) {
        SPLIT_POS(pos, x, y);
        auto* bomb = (Bomb*) game->getMap().getCase(x, y)->getItem();
        if (bomb) {
            bomb->explode();
            delete bomb;
            game->getMap().getCase(x, y)->setItem(nullptr);
        }
        else Log::warning("Bomb missing");
    }
    remoteBombs.clear();
}
