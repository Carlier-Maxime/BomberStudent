#include "Objects.h"

#include <utility>
#include "Player.h"
#include "Case.h"
#include "../utils/Utils.h"

Object::Object(std::string  type, Case &case_) : Item(case_), type(std::move(type)) {}

std::map<double, Object* (*)(Case&)> Object::objects = {
        {0.27, [](Case& case_) -> Object* {return new ObjectClassicBomb(case_);}},
        {0.13, [](Case& case_) -> Object* {return new ObjectRemoteBomb(case_);}},
        {0.1, [](Case& case_) -> Object* {return new ObjectMine(case_);}},
        {0.125, [](Case& case_) -> Object* {return new ObjectImpactUp(case_);}},
        {0.125, [](Case& case_) -> Object* {return new ObjectImpactDown(case_);}},
        {0.09, [](Case& case_) -> Object* {return new ObjectSpeedUp(case_);}},
        {0.09, [](Case& case_) -> Object* {return new ObjectSpeedDown(case_);}},
        {0.02, [](Case& case_) -> Object* {return new ObjectLifeMax(case_);}},
        {0.05, [](Case& case_) -> Object* {return new ObjectInvincible(case_);}}
};

Object *Object::getRandomObject(Case& case_) {
    if (objects.empty()) return nullptr;
    if (Utils::getRandomNumber()<0.7) return nullptr;
    double prob=Utils::getRandomNumber(), cumulate=0;
    for (const auto& obj : objects) {
        cumulate+=obj.first;
        if (prob<=cumulate) return obj.second(case_);
    }
    return nullptr;
}

const std::string &Object::getType() const {
    return type;
}

bool Object::get(Player *player) {
    if (!player) return false;
    if (action(*player)) {
        case_.setItem(nullptr);
        delete this;
    }
    return true;
}

ObjectClassicBomb::ObjectClassicBomb(Case &case_) : Object("classicBomb", case_) {}
ObjectRemoteBomb::ObjectRemoteBomb(Case &case_) : Object("remoteBomb", case_) {}
ObjectMine::ObjectMine(Case &case_) : Object("mine", case_) {}
ObjectImpactUp::ObjectImpactUp(Case &case_) : Object("impactUp", case_) {}
ObjectImpactDown::ObjectImpactDown(Case &case_) : Object("impactDown", case_) {}
ObjectSpeedUp::ObjectSpeedUp(Case &case_) : Object("speedUp", case_) {}
ObjectSpeedDown::ObjectSpeedDown(Case &case_) : Object("speedDown", case_) {}
ObjectLifeMax::ObjectLifeMax(Case &case_) : Object("lifeMax", case_) {}
ObjectInvincible::ObjectInvincible(Case &case_) : Object("invincible", case_) {}

bool ObjectClassicBomb::action(Player& player) {
    player.addClassicBomb();
    return true;
}

bool ObjectRemoteBomb::action(Player& player) {
    player.addRemoteBomb();
    return true;
}

bool ObjectMine::action(Player& player) {
    player.addMine();
    return true;
}

bool ObjectImpactUp::action(Player& player) {
    return player.incImpactDist();
}

bool ObjectImpactDown::action(Player& player) {
    return player.decImpactDist();
}

bool ObjectSpeedUp::action(Player& player) {
    player.speedUp();
    return true;
}

bool ObjectSpeedDown::action(Player& player) {
    player.speedDown();
    return true;
}

bool ObjectLifeMax::action(Player& player) {
    player.fullLife();
    return true;
}

bool ObjectInvincible::action(Player& player) {
    player.toInvincible();
    return true;
}
