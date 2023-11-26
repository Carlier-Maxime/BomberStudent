#ifndef BOMBER_STUDENT_CASENORMAL_H
#define BOMBER_STUDENT_CASENORMAL_H


#include "Case.h"

class CaseNormal : public Case {
public:
    [[nodiscard]] char getType() const override;
    [[nodiscard]] bool isAccessible() const override;
public:
    static const char type = '-';
};


#endif //BOMBER_STUDENT_CASENORMAL_H
