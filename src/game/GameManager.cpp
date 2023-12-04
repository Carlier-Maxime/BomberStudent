#include <sstream>
#include <algorithm>
#include "GameManager.h"
#include "../json/JSONMessage.h"

GameManager GameManager::instance = GameManager();

GameManager* GameManager::getInstance() {
    return &instance;
}

std::string GameManager::toJSON() {
    std::ostringstream json;
    json << R"("nbGamesList":)" << games.size();
    if(!games.empty()){
        json << R"(,"games":[)";
        for(u_int i=0; i<games.size(); i++){
            if(i>0) json << ',';
            json << games.at(i).toJSON();
        }
        json << ']';
    }
    return JSONMessage::actionMessage("game/list",200,"ok",json.str());
}

bool GameManager::isExist(const std::string& name) {
    return std::any_of(games.begin(), games.end(), [&name](const auto& game) {
        return game.getName() == name;
    });
}

Game* GameManager::addGame(const std::string& name, const Map& map) {
    games.emplace_back(name, map);
    return &games.back();
}

GameManager::GameManager() = default;

Game* GameManager::getGame(const std::string &name) {
    for (auto & game : games) if (game.getName()==name) return &game;
    return nullptr;
}

void GameManager::removeGame(const std::string &name) {
    for (auto it = games.begin(); it!=games.end(); it++) if (it->getName()==name) {
        games.erase(it);
        break;
    }
}
