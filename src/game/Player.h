#ifndef BOMBER_STUDENT_PLAYER_H
#define BOMBER_STUDENT_PLAYER_H


#include <string>

class Player {
private:
    std::string name;
    float speed;
    unsigned char life, nbClassicBomb, nbMine, nbRemoteBomb, impactDist, posX, posY;
    bool invincible;
public:
    explicit Player(std::string  name);
    [[nodiscard]] std::string toJSON() const;
    [[nodiscard]] std::string toJSONState() const;
    [[nodiscard]] const std::string &getName() const;
};


#endif //BOMBER_STUDENT_PLAYER_H
