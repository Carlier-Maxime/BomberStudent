#include "Objects.h"

#include <utility>
#include "Player.h"
#include "Case.h"
#include "../utils/Utils.h"
#include "../utils/ConstantMessages.h"

using CM = ConstantMessages;

Object::Object(Game& game, std::string  type, Case &case_) : Item(game, case_), type(std::move(type)) {}

std::map<double, Object* (*)(Game&, Case&)> Object::objects = {
        {0.27, [](Game& game, Case& case_) -> Object* {return new ObjectClassicBomb(game, case_);}},
        {0.13, [](Game& game, Case& case_) -> Object* {return new ObjectRemoteBomb(game, case_);}},
        {0.1, [](Game& game, Case& case_) -> Object* {return new ObjectMine(game, case_);}},
        {0.125, [](Game& game, Case& case_) -> Object* {return new ObjectImpactUp(game, case_);}},
        {0.125, [](Game& game, Case& case_) -> Object* {return new ObjectImpactDown(game, case_);}},
        {0.09, [](Game& game, Case& case_) -> Object* {return new ObjectSpeedUp(game, case_);}},
        {0.09, [](Game& game, Case& case_) -> Object* {return new ObjectSpeedDown(game, case_);}},
        {0.02, [](Game& game, Case& case_) -> Object* {return new ObjectLifeMax(game, case_);}},
        {0.05, [](Game& game, Case& case_) -> Object* {return new ObjectInvincible(game, case_);}}
};

Object *Object::getRandomObject(Game& game, Case& case_) {
    if (objects.empty()) return nullptr;
    if (Utils::getRandomNumber()<0.7) return nullptr;
    double prob=Utils::getRandomNumber(), cumulate=0;
    for (const auto& obj : objects) {
        cumulate+=obj.first;
        if (prob<=cumulate) return obj.second(game, case_);
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
        player->getSocket()->send(CM::postObjectNew+player->toJSONState());
        delete this;
    }
    return true;
}

ObjectClassicBomb::ObjectClassicBomb(Game& game, Case &case_) : Object(game, "classicBomb", case_) {}
ObjectRemoteBomb::ObjectRemoteBomb(Game& game, Case &case_) : Object(game, "remoteBomb", case_) {}
ObjectMine::ObjectMine(Game& game, Case &case_) : Object(game, "mine", case_) {}
ObjectImpactUp::ObjectImpactUp(Game& game, Case &case_) : Object(game, "impactUp", case_) {}
ObjectImpactDown::ObjectImpactDown(Game& game, Case &case_) : Object(game, "impactDown", case_) {}
ObjectSpeedUp::ObjectSpeedUp(Game& game, Case &case_) : Object(game, "speedUp", case_) {}
ObjectSpeedDown::ObjectSpeedDown(Game& game, Case &case_) : Object(game, "speedDown", case_) {}
ObjectLifeMax::ObjectLifeMax(Game& game, Case &case_) : Object(game, "lifeMax", case_) {}
ObjectInvincible::ObjectInvincible(Game& game, Case &case_) : Object(game, "invincible", case_) {}

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
