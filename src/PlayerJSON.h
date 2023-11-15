#ifndef BOMBER_STUDENT_PLAYER_JSON
#define BOMBER_STUDENT_PLAYER_JSON
#define PLAYER_JSON_STRING_PROTOTYPE "{\"name\":\"%s\",\"pos\":\"%d,%d\"}"

class PlayerJSON{
private:
	char* name;
	int posX;
	int posY;
public:
	PlayerJSON(char* nameValue,int posXValue, int posYValue);
	char* toJSON();
	char* getName();
};

#endif