#ifndef BOMBER_STUDENT_CASE_H
#define BOMBER_STUDENT_CASE_H


#include "Player.h"

class Item;

class Case {
private:
    Game* game;
    Player* player;
    Item* item;
    u_int16_t pos;
public:
    explicit Case(u_int16_t pos);
    [[nodiscard]] virtual char getType() const = 0;
    [[nodiscard]] virtual bool isAccessible() const = 0;
    [[nodiscard]] virtual Case* clone() const = 0;
    virtual void resetAccessible() = 0;
    virtual void toNoAccessible() = 0;
    virtual Case *explode(unsigned char &impactDist, float damage);
    void setPlayer(Player *player);
    [[nodiscard]] Item* getItem();
    void setItem(Item *item);
    void setGame(Game *game);
    [[nodiscard]] Game *getGame() const;
    virtual ~Case();
    [[nodiscard]] u_int16_t getPos() const;
    [[nodiscard]] Player *getPlayer() const;
};

#endif //BOMBER_STUDENT_CASE_H
