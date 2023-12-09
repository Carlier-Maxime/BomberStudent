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
    Map(const Map& other);
    Map& operator=(const Map& other) = default;
    [[nodiscard]] std::string toJSON() const;
    [[nodiscard]] unsigned int getId() const;
    [[nodiscard]] u_int16_t getRandomAvailablePos() const;
    Case* getCase(u_char x,u_char y);
    ~Map();
    [[nodiscard]] unsigned char getWidth() const;
    [[nodiscard]] unsigned char getHeight() const;
};


#endif //BOMBER_STUDENT_MAP_H