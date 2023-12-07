#include <sstream>
#include "MapManager.h"
#include "../json/JSONMessage.h"
#include "../utils/Log.h"

MapManager MapManager::mapManager = MapManager();

MapManager::MapManager() : maps() {
    maps.emplace_back(24,8,""
                           "************************"
                           "=----------------------="
                           "=----==============----="
                           "=----------****--------="
                           "=------****------------="
                           "=----==============----="
                           "=----------------------="
                           "************************");
}

MapManager *MapManager::getInstance() {
    return &mapManager;
}

std::string MapManager::toJSON() {
    std::ostringstream json;
    json << R"("nbMapsList":)" << maps.size() << R"(,"maps":[)";
    for(u_int i=0; i<maps.size(); i++){
        if(i>0) json << ',';
        json << maps[i].toJSON();
    }
    json << ']';
    return JSONMessage::actionMessage("maps/list", 200, "ok", json.str());
}

bool MapManager::isExist(unsigned int mapId) {
    return maps.size()>mapId && maps[mapId].getId()==mapId;
}

const Map& MapManager::get(unsigned int mapId) {
    if (!isExist(mapId)) throw std::invalid_argument("Unknown map id: "+std::to_string(mapId));
    return maps[mapId];
}
