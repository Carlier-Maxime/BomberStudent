#ifndef BOMBER_STUDENT_MAP_JSON
#define BOMBER_STUDENT_MAP_JSON


class MapJSON{
private:
	int id;
	int width;
	int height;
	char* content;
public:
	MapJSON(int idValue, int widthValue, int heightValue, char* contentValue);
	char* toJSON();
};


#define MAP_JSON_STRING_PROTOTYPE "{\"id\":%d,\"width\":%d,\"height\":%d,\"content\":\"%s\"}"
#endif