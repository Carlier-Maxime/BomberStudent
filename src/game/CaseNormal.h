#ifndef BOMBER_STUDENT_CASE_NORMAL_H
#define BOMBER_STUDENT_CASE_NORMAL_H


#include "Case.h"

class CaseNormal : public Case {
private:
    bool accessible;
public:
    explicit CaseNormal(u_int16_t pos);
    [[nodiscard]] char getType() const override;
    [[nodiscard]] bool isAccessible() const override;
    [[nodiscard]] Case *clone() const override;
    void resetAccessible() override;
    void toNoAccessible() override;

    Case *explode(unsigned char &impactDist, float damage) override;

    static const char type = '-';
};


#endif //BOMBER_STUDENT_CASE_NORMAL_H
