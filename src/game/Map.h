#ifndef BOMBER_STUDENT_MAP_H
#define BOMBER_STUDENT_MAP_H


#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include "Case.h"

class Map {
private:
    mutable std::mutex mutex;
    static unsigned int nextID;
    unsigned int id;
    unsigned char width, height;
    std::vector<Case*> cases;
    bool explodeCase(u_char x, u_char y, u_char &dist, float damage);
public:
    Map(unsigned char width, unsigned char height, const std::string& cases);
    Map(const Map& other);
    Map& operator=(const Map& other);
    [[nodiscard]] std::string toCasesString() const;
    [[nodiscard]] std::string toJSON() const;
    [[nodiscard]] unsigned int getId() const;
    [[nodiscard]] u_int16_t getRandomAvailablePos() const;
    Case* getCase(u_char x,u_char y);
    ~Map();
    [[nodiscard]] unsigned char getWidth() const;
    [[nodiscard]] unsigned char getHeight() const;
    void explodeBomb(u_char x, u_char y, u_char impactDist);
};


#endif //BOMBER_STUDENT_MAP_H
