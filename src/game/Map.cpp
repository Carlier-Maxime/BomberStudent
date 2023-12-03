#include <stdexcept>
#include <sstream>
#include "Map.h"
#include "CaseNormal.h"
#include "CaseWall.h"
#include "CaseUnbreakable.h"
#include "../utils/Log.h"
#include "../utils/Utils.h"

unsigned int Map::nextID = 0;

Map::Map(unsigned char width, unsigned char height, const std::string& cases) : id(nextID++), width(width), height(height), cases(width*height,nullptr) {
    if (width*height!=cases.size()) throw std::invalid_argument("cases string not content a correct number cases");
    Case* case_;
    for (unsigned int i=0; i<cases.size(); i++) {
        switch (cases[i]) {
            case '-':
                case_ = new CaseNormal();
                break;
            case '=':
                case_ = new CaseWall();
                break;
            case '*':
                case_ = new CaseUnbreakable();
                break;
            default:
                Log::warning("Unknown case type. case replaced by a normal case");
                case_ = new CaseNormal();
        }
        this->cases[i] = case_;
    }
}

std::string Map::toJSON() const {
    std::ostringstream json;
    json << "{\"id\":" << id << ",\"width\":" << std::to_string(width) << ",\"height\":" << std::to_string(height) << R"(,"content":")";
    for (auto* case_ : cases) json << case_->getType();
    json << "\"}";
    return json.str();
}

Map::~Map() {
    for (auto* case_ : cases) delete case_;
}

unsigned int Map::getId() const {
    return id;
}

u_int16_t Map::getRandomAvailablePos() const {
    std::vector<u_int> availablePos;
    for (unsigned int i=0; i<cases.size(); i++) if (cases[i]->isAccessible()) availablePos.push_back(i);
    u_int index = availablePos[Utils::getRandomNumber(0, cases.size()-1)];
    u_char y = index / width;
    u_char x = index % width;
    return (static_cast<u_int16_t>(y)<<8) | x;
}

bool Map::isAccessiblePos(unsigned char x, unsigned char y) {
    return cases[(static_cast<u_int16_t>(y)<<8) | x]->isAccessible();
}
