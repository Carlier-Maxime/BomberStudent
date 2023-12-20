#ifndef BOMBER_STUDENT_CASE_WALL_H
#define BOMBER_STUDENT_CASE_WALL_H


#include "Case.h"

class CaseWall : public Case {
public:
    [[nodiscard]] char getType() const override;
    [[nodiscard]] bool isAccessible() const override;
    Case *clone() const override;
    void resetAccessible() override;
    void toNoAccessible() override;
    Case *explode(unsigned char &impactDist, float damage) override;
public:
    explicit CaseWall(u_int16_t pos);
    static const char type = '=';
};


#endif //BOMBER_STUDENT_CASE_WALL_H
