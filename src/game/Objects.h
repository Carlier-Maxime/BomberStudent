#ifndef BOMBERSTUDENT_OBJECTS_H
#define BOMBERSTUDENT_OBJECTS_H

#include "Item.h"
#include <map>
#include <string>

class Object : public Item {
private:
    static std::map<double, Object* (*)(Game&, Case&)> objects;
    std::string type;
protected:
    virtual bool action(Player& player) = 0;
public:
    static Object* getRandomObject(Game& game, Case& case_);
    explicit Object(Game& game, std::string  type, Case &case_);
    [[nodiscard]] const std::string &getType() const;
    bool get(Player* player) override;
};

class ObjectClassicBomb : public Object {
public:
    explicit ObjectClassicBomb(Game& game, Case& case_);
    bool action(Player& player) override;
};

class ObjectRemoteBomb : public Object {
public:
    explicit ObjectRemoteBomb(Game& game, Case& case_);
    bool action(Player& player) override;
};

class ObjectMine : public Object {
public:
    explicit ObjectMine(Game& game, Case& case_);
    bool action(Player& player) override;
};

class ObjectImpactUp : public Object {
public:
    explicit ObjectImpactUp(Game& game, Case& case_);
    bool action(Player& player) override;
};

class ObjectImpactDown : public Object {
public:
    explicit ObjectImpactDown(Game& game, Case& case_);
    bool action(Player& player) override;
};

class ObjectSpeedUp : public Object {
public:
    explicit ObjectSpeedUp(Game& game, Case& case_);
    bool action(Player& player) override;
};

class ObjectSpeedDown : public Object {
public:
    explicit ObjectSpeedDown(Game& game, Case& case_);
    bool action(Player& player) override;
};

class ObjectLifeMax : public Object {
public:
    explicit ObjectLifeMax(Game& game, Case& case_);
    bool action(Player& player) override;
};

class ObjectInvincible : public Object {
public:
    explicit ObjectInvincible(Game& game, Case& case_);
    bool action(Player& player) override;
};

#endif //BOMBERSTUDENT_OBJECTS_H
