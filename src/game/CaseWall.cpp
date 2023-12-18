#include "CaseWall.h"
#include "CaseNormal.h"
#include "Objects.h"

char CaseWall::getType() const {
    return CaseWall::type;
}

bool CaseWall::isAccessible() const {
    return false;
}

Case *CaseWall::clone() const {
    return new CaseWall(*this);
}

void CaseWall::resetAccessible() {}

void CaseWall::toNoAccessible() {}

Case *CaseWall::explode(unsigned char &impactDist, float damage) {
    Case::explode(impactDist, damage);
    impactDist = impactDist>1 ? impactDist-2 : 0;
    auto case_ = new CaseNormal();
    case_->setItem(Object::getRandomObject(*case_));
    return case_;
}
