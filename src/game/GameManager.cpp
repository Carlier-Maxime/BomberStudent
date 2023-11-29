#include <sstream>
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

GameManager::GameManager() = default;
