#ifndef BOMBER_STUDENT_CASE_H
#define BOMBER_STUDENT_CASE_H


class Case {
public:
    [[nodiscard]] virtual char getType() const = 0;
    [[nodiscard]] virtual bool isAccessible() const = 0;
    [[nodiscard]] virtual Case* clone() const = 0;
    virtual void resetAccessible() = 0;
    virtual void toNoAccessible() = 0;
    virtual ~Case() = default;
};


#endif //BOMBER_STUDENT_CASE_H
