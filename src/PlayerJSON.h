#ifndef BOMBER_STUDENT_PLAYER_JSON
#define BOMBER_STUDENT_PLAYER_JSON

class PlayerJSON{
private:
	std::string name;
	int posX;
	int posY;
public:
	PlayerJSON(std::string nameValue,int posXValue, int posYValue);
	std::string toJSON() const;
	std::string getName() const;
};

#endif