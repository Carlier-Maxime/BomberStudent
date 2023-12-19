#ifndef BOMBERSTUDENT_OBJECTS_H
#define BOMBERSTUDENT_OBJECTS_H

#include "Item.h"
#include <map>

class Object : public Item {
private:
    static std::map<double, Object* (*)(Case&)> objects;
public:
    static Object* getRandomObject(Case& case_);
    explicit Object(Case& case_);
};

class ObjectClassicBomb : public Object {
public:
    explicit ObjectClassicBomb(Case& case_);
    bool get(Player *player) override;
};

class ObjectRemoteBomb : public Object {
public:
    explicit ObjectRemoteBomb(Case& case_);
    bool get(Player *player) override;
};

class ObjectMine : public Object {
public:
    explicit ObjectMine(Case& case_);
    bool get(Player *player) override;
};

class ObjectImpactUp : public Object {
public:
    explicit ObjectImpactUp(Case& case_);
    bool get(Player *player) override;
};

class ObjectImpactDown : public Object {
public:
    explicit ObjectImpactDown(Case& case_);
    bool get(Player *player) override;
};

class ObjectSpeedUp : public Object {
public:
    explicit ObjectSpeedUp(Case& case_);
    bool get(Player *player) override;
};

class ObjectSpeedDown : public Object {
public:
    explicit ObjectSpeedDown(Case& case_);
    bool get(Player *player) override;
};

class ObjectLifeMax : public Object {
public:
    explicit ObjectLifeMax(Case& case_);
    bool get(Player *player) override;
};

class ObjectInvincible : public Object {
public:
    explicit ObjectInvincible(Case& case_);
    bool get(Player *player) override;
};

#endif //BOMBERSTUDENT_OBJECTS_H
