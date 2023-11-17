#ifndef BOMBER_STUDENT_GAME_JSON
#define BOMBER_STUDENT_GAME_JSON
#define GAME_JSON_STRING_PROTOTYPE "{\"name\":\"%s\",\"nbPlayer\":%d,\"mapId\":%d}"
#define GAME_JSON_DETAIL_STRING_PROTOTYPE "{\"nbPlayer\":%d,\"mapId\":%d,\"startPos\":\"%d,%d\",\"player\":%s}"

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