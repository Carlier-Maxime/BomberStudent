#include <sstream>
#include "MapManager.h"

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
    std::ostringstream oss;
    oss << R"({"action":"maps/list", "statut":200,"message":"ok","nbMapsList":)" << maps.size() << ",\"maps\":[";
    for(u_int i=0; i<maps.size(); i++){
        if(i>0) oss << ",";
        oss << maps[i].toJSON();
    }
    oss << "]}";
    return oss.str();
}
