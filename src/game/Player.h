#ifndef BOMBER_STUDENT_PLAYER_H
#define BOMBER_STUDENT_PLAYER_H

#include <string>
#include "../socket/SocketTCP.h"

class Game;

class Player {
private:
    static const std::string possibleNames[];
    static std::string randomNames();
    const SocketTCP* socket;
    Game* game;
    std::string name;
    float speed;
    unsigned char life, nbClassicBomb, nbMine, nbRemoteBomb, impactDist, posX, posY;
    bool invincible;
protected:
public:
    explicit Player(const SocketTCP* socket, Game* game);
    [[nodiscard]] std::string toJSON() const;
    [[nodiscard]] std::string toJSONState() const;
    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] u_int16_t getPos() const;
    void move(unsigned char x, unsigned char y);
    [[nodiscard]] const SocketTCP* getSocket() const;
};


#endif //BOMBER_STUDENT_PLAYER_H
