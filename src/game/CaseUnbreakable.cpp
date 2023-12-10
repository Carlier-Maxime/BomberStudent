#include "CaseUnbreakable.h"

char CaseUnbreakable::getType() const {
    return CaseUnbreakable::type;
}

bool CaseUnbreakable::isAccessible() const {
    return false;
}

Case *CaseUnbreakable::clone() const {
    return new CaseUnbreakable(*this);
}

void CaseUnbreakable::resetAccessible() {}

void CaseUnbreakable::toNoAccessible() {}

Case *CaseUnbreakable::explode(unsigned char &impactDist) {
    impactDist=0;
    return nullptr;
}
