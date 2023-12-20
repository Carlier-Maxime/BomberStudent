#include "CaseNormal.h"

char CaseNormal::getType() const {
    return CaseNormal::type;
}

bool CaseNormal::isAccessible() const {
    return true;
}

Case *CaseNormal::clone() const {
    return new CaseNormal(*this);
}

void CaseNormal::resetAccessible() {
    accessible=true;
}

void CaseNormal::toNoAccessible() {
    accessible=false;
}

CaseNormal::CaseNormal(u_int16_t pos) : Case(pos), accessible(true) {}

Case *CaseNormal::explode(unsigned char &impactDist, float damage) {
    Case::explode(impactDist, damage);
    impactDist--;
    return nullptr;
}
