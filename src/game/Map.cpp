#include <stdexcept>
#include <sstream>
#include "Map.h"
#include "CaseNormal.h"
#include "CaseWall.h"
#include "CaseUnbreakable.h"
#include "../utils/Log.h"
#include "../utils/Utils.h"
#include "../utils/ConstantMessages.h"
#include "Objects.h"

using CM = ConstantMessages;

unsigned int Map::nextID = 0;

Map::Map(unsigned char width, unsigned char height, const std::string& cases) : id(nextID++), width(width), height(height), cases(width*height,nullptr) {
    if (width*height!=cases.size()) throw std::invalid_argument("cases string not content a correct number cases");
    Case* case_;
    for (unsigned int i=0; i<cases.size(); i++) {
        switch (cases[i]) {
            case '-':
                case_ = new CaseNormal();
                case_->setItem(Object::getRandomObject(*case_));
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
                case_->setItem(Object::getRandomObject(*case_));
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

std::string Map::toCasesString() const {
    std::ostringstream str;
    for (auto* case_ : cases) str << case_->getType();
    return str.str();
}

std::string Map::toJSON() const {
    std::ostringstream json;
    json << "{\"id\":" << id << ",\"width\":" << std::to_string(width) << ",\"height\":" << std::to_string(height) << R"(,"content":")";
    json << toCasesString() << "\"}";
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

void Map::explodeBomb(u_char x, u_char y, u_char impactDist, float (*damage)(u_char distOfImpact)) {
    std::lock_guard<std::mutex> lock(mutex);
    u_char dist, i, j;
    for (j=0, i=x,dist=impactDist+1; dist>0 && explodeCase(i, y, dist, damage(j)); i= (i==width-1) ? 0 : i+1, j++);
    for (j=1, i=x-1,dist=impactDist; dist>0 && explodeCase(i, y, dist, damage(j)); i= (i==0) ? width-1 : i-1, j++);
    for (j=1, i=y+1,dist=impactDist; dist>0 && explodeCase(x, i, dist, damage(j)); i= (i==height-1) ? 0 : i+1, j++);
    for (j=1, i=y-1,dist=impactDist; dist>0 && explodeCase(x, i, dist, damage(j)); i= (i==0) ? height-1 : i-1, j++);
}

bool Map::explodeCase(u_char x, u_char y, u_char &dist, float damage) {
    auto* case_ = getCase(x,y);
    if (case_) case_ = case_->explode(dist, damage);
    else return false;
    if (case_) {
        u_int index = static_cast<u_int>(y)*width+static_cast<u_int>(x);
        delete cases[index];
        cases[index] = case_;
    }
    return true;
}

std::string Map::toObjectsJSON() const {
    std::ostringstream oss;
    oss << '[';
    Object* obj;
    u_char x, y=height;
    for (size_t pos=0; pos<cases.size(); pos++) if ((obj=dynamic_cast<Object*>(cases[pos]->getItem()))) {
        if (y!=height) oss << ',';
        y = pos / width;
        x = pos % width;
        oss << R"({"type":")" << obj->getType() << R"(","pos":")" << std::to_string(x) << ',' << std::to_string(y) << "\"}";
    }
    oss << ']';
    return oss.str();
}
