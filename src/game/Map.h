#ifndef BOMBER_STUDENT_MAP_H
#define BOMBER_STUDENT_MAP_H


#include <vector>
#include <string>
#include "Case.h"

class Map {
private:
    static unsigned int nextID;
    unsigned int id;
    unsigned char width, height;
    std::vector<Case*> cases;
public:
    Map(unsigned char width, unsigned char height, const std::string& cases);
    [[nodiscard]] std::string toJSON() const;
    ~Map();
};


#endif //BOMBER_STUDENT_MAP_H
