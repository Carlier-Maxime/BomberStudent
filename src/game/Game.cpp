#include "Game.h"
#include "../utils/Utils.h"
#include "../json/JSONMessage.h"
#include "GameManager.h"

#include <utility>
#include <sstream>

Game::Game(std::string name, const Map &map) : mutex(), name(std::move(name)), map(map), players() {}

Game::Game(const Game &other) : mutex(), name(other.name), map(other.map){}

Game &Game::operator=(const Game &other) {
    if (this != &other) {
        name = other.name;
        map = other.map;
    }
    return *this;
}

std::string Game::toJSON() const{
    std::ostringstream json;
    json << R"({"name":")" << name << R"(","nbPlayer":)"<< players.size() << ",\"mapId\":" << map.getId() << "}";
    return json.str();
}

const std::string &Game::getName() const {
    return name;
}

Player* Game::newPlayer() {
    std::lock_guard<std::shared_mutex> lock(mutex);
    players.emplace_back(this);
    u_int16_t pos = map.getRandomAvailablePos();
    u_char x, y;
    SPLIT_POS(pos,x,y);
    Player* player = &players.back();
    player->move(x,y);
    return player;
}

bool Game::isAccessiblePos(unsigned char x, unsigned char y) {
    return map.isAccessiblePos(x, y);
}

std::string Game::jsonCreateOrJoinGame(const Player &player) {
    std::shared_lock<std::shared_mutex> lock(mutex);
    std::ostringstream json;
    unsigned char posX, posY;
    SPLIT_POS(player.getPos(), posX, posY);
    u_int nbPlayers = players.size()-1;
    json << R"("nbPlayers":)"<<nbPlayers<<R"(","mapId":)"<<map.getId();
    if (nbPlayers) {
        json << R"(,"players":[)";
        for (u_int i=0; i<players.size(); i++) {
            if (players[i].getPos()==player.getPos()) continue;
            if (i) json << ',';
            json << players[i].toJSON();
        }
        json << ']';
    }
    json << R"(,"startPos":")"<<std::to_string(posX)<<','<<std::to_string(posY)<<R"(","player":)"<<player.toJSONState();
    return JSONMessage::actionMessage(nbPlayers ? "game/join" : "game/create", 201, nbPlayers ? "game joined" : "game created", json.str());
}

void Game::removePlayer(const Player &player) {
    std::lock_guard<std::shared_mutex> lock(mutex);
    for (auto it=players.begin(); it!=players.end(); it++) if (it->getPos()==player.getPos()) {
        players.erase(it);
        break;
    }
    if (players.empty()) GameManager::getInstance()->removeGame(name);
}
