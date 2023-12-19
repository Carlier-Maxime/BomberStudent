#ifndef BOMBERSTUDENT_ITEM_H
#define BOMBERSTUDENT_ITEM_H


class Player;
class Case;

class Item {
protected:
    Case& case_;
public:
    explicit Item(Case& case_);
    virtual bool get(Player *player) = 0;
    virtual ~Item() = default;
};


#endif //BOMBERSTUDENT_ITEM_H
