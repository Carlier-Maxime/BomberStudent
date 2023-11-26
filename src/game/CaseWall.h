#ifndef BOMBER_STUDENT_CASE_WALL_H
#define BOMBER_STUDENT_CASE_WALL_H


#include "Case.h"

class CaseWall : public Case {
public:
    [[nodiscard]] char getType() const override;
    [[nodiscard]] bool isAccessible() const override;

public:
    static const char type = '=';
};


#endif //BOMBER_STUDENT_CASE_WALL_H
