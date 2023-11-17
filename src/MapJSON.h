#ifndef BOMBER_STUDENT_MAP_JSON
#define BOMBER_STUDENT_MAP_JSON


class MapJSON{
private:
	int id;
	int width;
	int height;
	std::string content;
public:
	MapJSON(int idValue, int widthValue, int heightValue, std::string contentValue);
	std::string toJSON() const;
};
#endif