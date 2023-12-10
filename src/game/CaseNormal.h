#ifndef BOMBER_STUDENT_CASE_NORMAL_H
#define BOMBER_STUDENT_CASE_NORMAL_H


#include "Case.h"

class CaseNormal : public Case {
private:
    bool accessible;
public:
    CaseNormal();
    [[nodiscard]] char getType() const override;
    [[nodiscard]] bool isAccessible() const override;
    [[nodiscard]] Case *clone() const override;
    void resetAccessible() override;
    void toNoAccessible() override;

    Case *explode(unsigned char &impactDist) override;

    static const char type = '-';
};


#endif //BOMBER_STUDENT_CASE_NORMAL_H
