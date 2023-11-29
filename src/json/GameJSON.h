#ifndef BOMBER_STUDENT_GAME_JSON
#define BOMBER_STUDENT_GAME_JSON

#include "../game/Player.h"

class GameJSON{
private:
	std::string name;
	int nbPlayer;
	std::vector<Player*> players;
	int mapId;
	int startPos[2];
	Player* playerStateJSON;
public:
	GameJSON(std::string nameValue,std::vector<Player*> playersValue, int mapIdValue,int startPosValue[], Player* playerStateJSONValue);
	std::string toJSON() const;
	std::string toDetailJSON() const;
	Player* getPlayerState() const;
	int getMapId() const;
	int* getStartPos();
	std::vector<Player*> getPlayers() const;
};

#endif