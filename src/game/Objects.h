#ifndef BOMBERSTUDENT_OBJECTS_H
#define BOMBERSTUDENT_OBJECTS_H

#include "Item.h"
#include <map>
#include <string>

class Object : public Item {
private:
    static std::map<double, Object* (*)(Case&)> objects;
    std::string type;
protected:
    virtual bool action(Player& player) = 0;
public:
    static Object* getRandomObject(Case& case_);
    explicit Object(std::string  type, Case &case_);
    [[nodiscard]] const std::string &getType() const;
    bool get(Player* player) override;
};

class ObjectClassicBomb : public Object {
public:
    explicit ObjectClassicBomb(Case& case_);
    bool action(Player& player) override;
};

class ObjectRemoteBomb : public Object {
public:
    explicit ObjectRemoteBomb(Case& case_);
    bool action(Player& player) override;
};

class ObjectMine : public Object {
public:
    explicit ObjectMine(Case& case_);
    bool action(Player& player) override;
};

class ObjectImpactUp : public Object {
public:
    explicit ObjectImpactUp(Case& case_);
    bool action(Player& player) override;
};

class ObjectImpactDown : public Object {
public:
    explicit ObjectImpactDown(Case& case_);
    bool action(Player& player) override;
};

class ObjectSpeedUp : public Object {
public:
    explicit ObjectSpeedUp(Case& case_);
    bool action(Player& player) override;
};

class ObjectSpeedDown : public Object {
public:
    explicit ObjectSpeedDown(Case& case_);
    bool action(Player& player) override;
};

class ObjectLifeMax : public Object {
public:
    explicit ObjectLifeMax(Case& case_);
    bool action(Player& player) override;
};

class ObjectInvincible : public Object {
public:
    explicit ObjectInvincible(Case& case_);
    bool action(Player& player) override;
};

#endif //BOMBERSTUDENT_OBJECTS_H
