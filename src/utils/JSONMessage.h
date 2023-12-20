#ifndef BOMBER_STUDENT_JSON_MESSAGE
#define BOMBER_STUDENT_JSON_MESSAGE

#include <vector>
#include "../game/Map.h"
#include "../game/Player.h"

class JSONMessage{
private:
public:
	static std::string errorMessage(int statut, const std::string& message);
    static std::string actionMessage(const std::string& action, int statut, const std::string& message, const std::string& jsonContent);
};

#endif