#ifndef BOMBER_STUDENT_PLAYER_H
#define BOMBER_STUDENT_PLAYER_H

#include <string>

class Game;

class Player {
private:
    static const std::string possibleNames[];
    static std::string randomNames();
    Game* game;
    std::string name;
    float speed;
    unsigned char life, nbClassicBomb, nbMine, nbRemoteBomb, impactDist, posX, posY;
    bool invincible;
protected:
public:
    explicit Player(Game* game);
    [[nodiscard]] std::string toJSON() const;
    [[nodiscard]] std::string toJSONState() const;
    [[nodiscard]] const std::string &getName() const;
    void move(unsigned char x, unsigned char y);
};


#endif //BOMBER_STUDENT_PLAYER_H
