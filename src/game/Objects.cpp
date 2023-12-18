#include "Objects.h"
#include "Player.h"
#include "Case.h"

ObjectClassicBomb::ObjectClassicBomb(Case &case_) : Item(case_) {}
ObjectRemoteBomb::ObjectRemoteBomb(Case &case_) : Item(case_) {}
ObjectMine::ObjectMine(Case &case_) : Item(case_) {}
ObjectImpactUp::ObjectImpactUp(Case &case_) : Item(case_) {}
ObjectImpactDown::ObjectImpactDown(Case &case_) : Item(case_) {}
ObjectSpeedUp::ObjectSpeedUp(Case &case_) : Item(case_) {}
ObjectSpeedDown::ObjectSpeedDown(Case &case_) : Item(case_) {}
ObjectLifeMax::ObjectLifeMax(Case &case_) : Item(case_) {}
ObjectInvincible::ObjectInvincible(Case &case_) : Item(case_) {}

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
