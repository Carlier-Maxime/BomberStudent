#include "Game.h"
#include "../utils/Utils.h"
#include "../json/JSONMessage.h"
#include "GameManager.h"
#include "../utils/ConstantMessages.h"

#include <utility>
#include <sstream>
#include <thread>

using CM = ConstantMessages;

Game::Game(std::string name, const Map &map) : mutex(), name(std::move(name)), map(map), players(), started(false) {}

Game::Game(const Game &other) : mutex(), name(other.name), map(other.map), started(false) {}

Game &Game::operator=(const Game &other) {
    if (this != &other) {
        name = other.name;
        map = other.map;
        players = other.players;
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

Player * Game::newPlayer(const SocketTCP *socket) {
    if (isStarted()) return nullptr;
    std::lock_guard<std::shared_mutex> lock(mutex);
    u_int16_t pos = map.getRandomAvailablePos();
    u_char x, y;
    SPLIT_POS(pos,x,y);
    players.emplace_back(socket, this, x, y);
    map.getCase(x,y)->toNoAccessible();
    Player* player = &players.back();
    return player;
}

std::string Game::jsonCreateOrJoinGame(const Player &player) {
    std::shared_lock<std::shared_mutex> lock(mutex);
    std::ostringstream json;
    unsigned char posX, posY;
    SPLIT_POS(player.getPos(), posX, posY);
    u_int nbPlayers = players.size()-1;
    json << R"("nbPlayers":)"<<nbPlayers<<R"(,"mapId":)"<<map.getId();
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

bool Game::isStarted() const {
    return started;
}

void Game::start(const Player& player) {
    if (!started && !players.empty() && player.getPos()==players[0].getPos()) {
        std::thread go([this](){
            sendForAllPlayers(CM::postGameReady);
            std::this_thread::sleep_for(std::chrono::seconds(3));
            started=true;
            sendForAllPlayers(CM::postGameGo);
        });
        go.detach();
    }
}

void Game::sendForAllPlayers(const std::string& msg) const {
    for (const auto& player : players) player.getSocket()->send(msg);
}

u_char Game::getWidth() {
    return map.getWidth();
}

u_char Game::getHeight() {
    return map.getHeight();
}

Map &Game::getMap() {
    return map;
}