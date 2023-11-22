#ifndef BOMBER_STUDENT_JSON_MESSAGE
#define BOMBER_STUDENT_JSON_MESSAGE

#define STATUT_OK 200

class JSONMessage{
private:
public:
	JSONMessage();
	std::string errorMessage(int statut, std::string message) const;
	std::string mapsListMessage(std::vector<MapJSON*> maps, int nbMaps) const;
	std::string gamesListMessage(std::vector<GameJSON*> maps, int nbGames) const;
	std::string gameCreatedMessage(GameJSON* game) const;
	std::string joinGameMessage(GameJSON* game) const;
	std::string playerPositionUpdateMessage(PlayerJSON* player, std::string dir) const;
	std::string updatePoseBombPlayerMessage(PlayerStateJSON* playerState, int posX, int posY) const;
	std::string alertBombPosedMessage(int posX, int posY, std::string type) const;
	std::string alertBombExplodedMessage(int posX, int posY, std::string type, int impactDist, std::string map) const;
	std::string alertAttackAffectMessage(PlayerStateJSON* playerState) const;
	std::string bonusUpdateMessage(PlayerStateJSON* playerState) const;
};

#endif