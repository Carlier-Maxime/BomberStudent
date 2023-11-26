#ifndef BOMBER_STUDENT_GAME_JSON
#define BOMBER_STUDENT_GAME_JSON

#include "PlayerJSON.h"
#include "PlayerStateJSON.h"

class GameJSON{
private:
	std::string name;
	int nbPlayer;
	std::vector<PlayerJSON*> players;
	int mapId;
	int startPos[2];
	PlayerStateJSON* playerStateJSON;
public:
	GameJSON(std::string nameValue,std::vector<PlayerJSON*> playersValue, int mapIdValue,int startPosValue[], PlayerStateJSON* playerStateJSONValue);
	std::string toJSON() const;
	std::string toDetailJSON() const;
	PlayerStateJSON* getPlayerState() const;
	int getMapId() const;
	int* getStartPos();
	std::vector<PlayerJSON*> getPlayers() const;
};

#endif