#ifndef BOMBER_STUDENT_MAP_H
#define BOMBER_STUDENT_MAP_H


#include <vector>
#include <string>
#include "Case.h"

#define SPLIT_POS(pos, x, y) \
    do { \
        y = static_cast<uint8_t>((pos) >> 8); \
        x = static_cast<uint8_t>((pos) & 0xFF); \
    } while(0)

class Map {
private:
    static unsigned int nextID;
    unsigned int id;
    unsigned char width, height;
    std::vector<Case*> cases;
public:
    Map(unsigned char width, unsigned char height, const std::string& cases);
    [[nodiscard]] std::string toJSON() const;
    [[nodiscard]] unsigned int getId() const;
    [[nodiscard]] u_int16_t getRandomAvailablePos() const;
    bool isAccessiblePos(unsigned char x, unsigned char y);
    ~Map();
};


#endif //BOMBER_STUDENT_MAP_H
