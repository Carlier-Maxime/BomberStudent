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
	static std::string playerPositionUpdateMessage(Player* player, const std::string& dir);
	static std::string updatePoseBombPlayerMessage(Player* playerState, int posX, int posY);
	static std::string alertBombPosedMessage(int posX, int posY, const std::string& type);
	static std::string alertBombExplodedMessage(int posX, int posY, const std::string& type, int impactDist, const std::string& map);
	static std::string alertAttackAffectMessage(Player* playerState);
	static std::string bonusUpdateMessage(Player* playerState);
};

#endif