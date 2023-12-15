#include "CaseWall.h"
#include "CaseNormal.h"

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

Case *CaseWall::explode(unsigned char &impactDist) {
    Case::explode(impactDist);
    impactDist = impactDist>1 ? impactDist-2 : 0;
    return new CaseNormal();
}
