#ifndef BOMBER_STUDENT_JSON_MESSAGE
#define BOMBER_STUDENT_JSON_MESSAGE

#include <vector>
#include "MapJSON.h"
#include "GameJSON.h"
#include "PlayerJSON.h"
#include "PlayerStateJSON.h"

class JSONMessage{
private:
public:
	static std::string errorMessage(int statut, const std::string& message) ;
	static std::string mapsListMessage(std::vector<MapJSON*> maps, int nbMaps) ;
	static std::string gamesListMessage(std::vector<GameJSON*> maps, int nbGames) ;
	static std::string gameCreatedMessage(GameJSON* game) ;
	static std::string joinGameMessage(GameJSON* game) ;
	static std::string playerPositionUpdateMessage(PlayerJSON* player, const std::string& dir) ;
	static std::string updatePoseBombPlayerMessage(PlayerStateJSON* playerState, int posX, int posY) ;
	static std::string alertBombPosedMessage(int posX, int posY, const std::string& type) ;
	static std::string alertBombExplodedMessage(int posX, int posY, const std::string& type, int impactDist, const std::string& map) ;
	static std::string alertAttackAffectMessage(PlayerStateJSON* playerState) ;
	static std::string bonusUpdateMessage(PlayerStateJSON* playerState) ;
};

#endif