#include <stdexcept>
#include <sstream>
#include "Map.h"
#include "CaseNormal.h"
#include "CaseWall.h"
#include "CaseUnbreakable.h"
#include "../utils/Log.h"
#include "../utils/Utils.h"
#include "../utils/Config.h"

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

Map::Map(const Map& other) : id(other.id), width(other.width), height(other.height), cases(other.cases.size(), nullptr) {
    try {
        for (unsigned int i = 0; i < other.cases.size(); i++) if (other.cases[i]) cases[i] = other.cases[i]->clone();
    } catch (...) {
        for (auto* case_ : cases) delete case_;
        throw;
    }
}

Map &Map::operator=(const Map &other) {
    if (this != &other) {
        try {
            for (unsigned int i = 0; i < other.cases.size(); i++) if (other.cases[i]) cases[i] = other.cases[i]->clone();
        } catch (...) {
            for (auto* case_ : cases) delete case_;
            throw;
        }
        width = other.width;
        height = other.height;
        id = other.id;
    }
    return *this;
}

std::string Map::toJSON() const {
    std::ostringstream json;
    json << "{\"id\":" << id << ",\"width\":" << std::to_string(width) << ",\"height\":" << std::to_string(height) << R"(,"content":")";
    for (auto* case_ : cases) json << case_->getType();
    json << "\"}";
    return json.str();
}

Map::~Map() {
    for (auto &th : classicBombs) th.join();
    for (auto* case_ : cases) delete case_;
}

unsigned int Map::getId() const {
    return id;
}

u_int16_t Map::getRandomAvailablePos() const {
    std::vector<u_int> availablePos;
    for (unsigned int i=0; i<cases.size(); i++) if (cases[i]->isAccessible()) availablePos.push_back(i);
    u_int index = availablePos[Utils::getRandomNumber(0, availablePos.size()-1)];
    u_char y = index / width;
    u_char x = index % width;
    return MERGE_POS(x,y);
}

unsigned char Map::getWidth() const {
    return width;
}

unsigned char Map::getHeight() const {
    return height;
}

Case *Map::getCase(u_char x, u_char y) {
    if (x<width && y<height) return cases[static_cast<u_int>(y)*width+static_cast<u_int>(x)];
    return nullptr;
}

void Map::explodeBomb(u_char x, u_char y, u_char impactDist) {
    std::lock_guard<std::mutex> lock(mutex);
    u_char dist = impactDist;
    u_char i = x;
    for (;dist>0 && explodeCase(i,y,dist);i++);
    explodeCase(i,y,dist);
    i=x-1;
    dist = impactDist==0 ? 0 : impactDist-1;
    for (;dist>0 && explodeCase(i,y,dist);i--);
    explodeCase(i,y,dist);
    i=y;
    dist = impactDist==0 ? 0 : impactDist-1;
    for (;dist>0 && explodeCase(x,i,dist);i++);
    explodeCase(x,i,dist);
    i=y-1;
    dist = impactDist==0 ? 0 : impactDist-1;
    for (;dist>0 && explodeCase(x,i,dist);i--);
    explodeCase(x,i,dist);
}

bool Map::explodeCase(u_char x, u_char y, u_char &dist) {
    auto* case_ = getCase(x,y);
    if (case_) case_ = case_->explode(dist);
    else return false;
    if (case_) {
        u_int index = static_cast<u_int>(y)*width+static_cast<u_int>(x);
        delete cases[index];
        cases[index] = case_;
    }
    return true;
}

void Map::armBomb(u_char x, u_char y, u_char impactDist) {
    classicBombs.emplace_back([this,x,y,impactDist](){
        std::this_thread::sleep_for(std::chrono::seconds(Config::getDetonationTime()));
        explodeBomb(x,y,impactDist);
    });
}
