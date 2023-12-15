#ifndef BOMBER_STUDENT_CASE_H
#define BOMBER_STUDENT_CASE_H


#include "Player.h"

class Case {
private:
    Player* player;
public:
    Case();
    [[nodiscard]] virtual char getType() const = 0;
    [[nodiscard]] virtual bool isAccessible() const = 0;
    [[nodiscard]] virtual Case* clone() const = 0;
    virtual void resetAccessible() = 0;
    virtual void toNoAccessible() = 0;
    virtual Case* explode(unsigned char& impactDist) = 0;
    [[nodiscard]] Player *getPlayer() const;
    void setPlayer(Player *player);
    virtual ~Case() = default;
};

#endif //BOMBER_STUDENT_CASE_H
