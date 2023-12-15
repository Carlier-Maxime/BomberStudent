#ifndef BOMBER_STUDENT_PLAYER_H
#define BOMBER_STUDENT_PLAYER_H

#include <chrono>
#include <string>
#include "../socket/SocketTCP.h"

class Game;

class Player {
private:
    static u_int id;
    static const std::string possibleNames[];
    static std::string randomNames();
    const SocketTCP* socket;
    Game* game;
    std::string name;
    float speed;
    unsigned char life, nbClassicBomb, nbMine, nbRemoteBomb, impactDist, posX, posY;
    bool invincible;
    std::chrono::high_resolution_clock::time_point timeLastMove;
protected:
public:
    explicit Player(const SocketTCP* socket, Game* game, u_char posX, u_char posY);
    [[nodiscard]] std::string toJSON() const;
    [[nodiscard]] std::string toJSONState() const;
    [[nodiscard]] const std::string &getName() const;
    [[nodiscard]] u_int16_t getPos() const;
    bool move(unsigned char x, unsigned char y);
    bool move(const std::string& direction);
    [[nodiscard]] const SocketTCP* getSocket() const;
    [[nodiscard]] std::string toJSONMove(const std::string& direction) const;
    bool poseBomb(const std::string &type);
    [[nodiscard]] std::string toJSONAttackBomb() const;
    [[nodiscard]] std::string toJSONAttackNewBomb(const std::string &type) const;
    void takeDamage(u_char damage);
};


#endif //BOMBER_STUDENT_PLAYER_H
