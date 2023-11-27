#ifndef BOMBER_STUDENT_MAPMANAGER_H
#define BOMBER_STUDENT_MAPMANAGER_H


#include <vector>
#include "Map.h"

class MapManager {
private:
    static MapManager mapManager;
    std::vector<Map> maps;
    MapManager();
public:
    static MapManager* getInstance();
    std::string toJSON();
};


#endif //BOMBER_STUDENT_MAPMANAGER_H
