#include <sstream>
#include "GameManager.h"

GameManager GameManager::instance = GameManager();

GameManager* GameManager::getInstance() {
    return &instance;
}

std::string GameManager::toJSON() {
    std::string action = "game/list";
    std::ostringstream oss;
    oss << R"({"action":")" << action << R"(", "statut":200,"message":"ok","nbGamesList":)" << games.size();
    if(!games.empty()){
        oss << "\"games\":[";
        for(u_int i=0; i<games.size(); i++){
            if(i>0) oss << ',';
            oss << games.at(i).toJSON();
        }
        oss << ']';
    }
    oss << '}';
    return oss.str();
}

GameManager::GameManager() = default;
