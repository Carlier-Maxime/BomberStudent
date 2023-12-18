#ifndef BOMBERSTUDENT_OBJECTS_H
#define BOMBERSTUDENT_OBJECTS_H

#include "Item.h"

class ObjectClassicBomb : public Item {
public:
    bool get(Player *player) override;
};

class ObjectRemoteBomb : public Item {
public:
    bool get(Player *player) override;
};

class ObjectMine : public Item {
public:
    bool get(Player *player) override;
};

class ObjectImpactUp : public Item {
public:
    bool get(Player *player) override;
};

class ObjectImpactDown : public Item {
public:
    bool get(Player *player) override;
};

class ObjectSpeedUp : public Item {
public:
    bool get(Player *player) override;
};

class ObjectSpeedDown : public Item {
public:
    bool get(Player *player) override;
};

class ObjectLifeMax : public Item {
public:
    bool get(Player *player) override;
};

class ObjectInvincible : public Item {
public:
    bool get(Player *player) override;
};

#endif //BOMBERSTUDENT_OBJECTS_H
