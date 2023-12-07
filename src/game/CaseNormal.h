#ifndef BOMBER_STUDENT_CASE_NORMAL_H
#define BOMBER_STUDENT_CASE_NORMAL_H


#include "Case.h"

class CaseNormal : public Case {
public:
    [[nodiscard]] char getType() const override;
    [[nodiscard]] bool isAccessible() const override;

    Case *clone() const override;

public:
    static const char type = '-';
};


#endif //BOMBER_STUDENT_CASE_NORMAL_H
