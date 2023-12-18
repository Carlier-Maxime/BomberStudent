#ifndef BOMBERSTUDENT_OBJECTS_H
#define BOMBERSTUDENT_OBJECTS_H

#include "Item.h"

class ObjectClassicBomb : public Item {
public:
    explicit ObjectClassicBomb(Case& case_);
    bool get(Player *player) override;
};

class ObjectRemoteBomb : public Item {
public:
    explicit ObjectRemoteBomb(Case& case_);
    bool get(Player *player) override;
};

class ObjectMine : public Item {
public:
    explicit ObjectMine(Case& case_);
    bool get(Player *player) override;
};

class ObjectImpactUp : public Item {
public:
    explicit ObjectImpactUp(Case& case_);
    bool get(Player *player) override;
};

class ObjectImpactDown : public Item {
public:
    explicit ObjectImpactDown(Case& case_);
    bool get(Player *player) override;
};

class ObjectSpeedUp : public Item {
public:
    explicit ObjectSpeedUp(Case& case_);
    bool get(Player *player) override;
};

class ObjectSpeedDown : public Item {
public:
    explicit ObjectSpeedDown(Case& case_);
    bool get(Player *player) override;
};

class ObjectLifeMax : public Item {
public:
    explicit ObjectLifeMax(Case& case_);
    bool get(Player *player) override;
};

class ObjectInvincible : public Item {
public:
    explicit ObjectInvincible(Case& case_);
    bool get(Player *player) override;
};

#endif //BOMBERSTUDENT_OBJECTS_H
