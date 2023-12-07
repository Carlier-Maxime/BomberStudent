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
