#include "Objects.h"
#include "Player.h"
#include "Case.h"
#include "../utils/Utils.h"

Object::Object(Case &case_) : Item(case_) {}

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

ObjectClassicBomb::ObjectClassicBomb(Case &case_) : Object(case_) {}
ObjectRemoteBomb::ObjectRemoteBomb(Case &case_) : Object(case_) {}
ObjectMine::ObjectMine(Case &case_) : Object(case_) {}
ObjectImpactUp::ObjectImpactUp(Case &case_) : Object(case_) {}
ObjectImpactDown::ObjectImpactDown(Case &case_) : Object(case_) {}
ObjectSpeedUp::ObjectSpeedUp(Case &case_) : Object(case_) {}
ObjectSpeedDown::ObjectSpeedDown(Case &case_) : Object(case_) {}
ObjectLifeMax::ObjectLifeMax(Case &case_) : Object(case_) {}
ObjectInvincible::ObjectInvincible(Case &case_) : Object(case_) {}

bool ObjectClassicBomb::get(Player *player) {
    if (!player) return false;
    player->addClassicBomb();
    case_.setItem(nullptr);
    delete this;
    return true;
}

bool ObjectRemoteBomb::get(Player *player) {
    if (!player) return false;
    player->addRemoteBomb();
    case_.setItem(nullptr);
    delete this;
    return true;
}

bool ObjectMine::get(Player *player) {
    if (!player) return false;
    player->addMine();
    case_.setItem(nullptr);
    delete this;
    return true;
}

bool ObjectImpactUp::get(Player *player) {
    if (!player) return false;
    if (player->incImpactDist()) {
        case_.setItem(nullptr);
        delete this;
    }
    return true;
}

bool ObjectImpactDown::get(Player *player) {
    if (!player) return false;
    if (player->decImpactDist()) {
        case_.setItem(nullptr);
        delete this;
    }
    return true;
}

bool ObjectSpeedUp::get(Player *player) {
    if (!player) return false;
    player->speedUp();
    case_.setItem(nullptr);
    delete this;
    return true;
}

bool ObjectSpeedDown::get(Player *player) {
    if (!player) return false;
    player->speedDown();
    case_.setItem(nullptr);
    delete this;
    return true;
}

bool ObjectLifeMax::get(Player *player) {
    if (!player) return false;
    player->fullLife();
    case_.setItem(nullptr);
    delete this;
    return true;
}

bool ObjectInvincible::get(Player *player) {
    if (!player) return false;
    player->toInvincible();
    case_.setItem(nullptr);
    delete this;
    return true;
}
