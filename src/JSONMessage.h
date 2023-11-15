#ifndef BOMBER_STUDENT_JSON_MESSAGE
#define BOMBER_STUDENT_JSON_MESSAGE

#define STATUT_MESSAGE_STRING_PROTOTYPE "\"statut\":\"%d\",\"message\":\"%s\""
#define ACTION_MESSAGE_STRING_PROTOTYPE "\"action\":\"%s\""

#define MAP_LIST_MESSAGE_STRING_PROTOTYPE "{" ACTION_MESSAGE_STRING_PROTOTYPE "," STATUT_MESSAGE_STRING_PROTOTYPE ",\"nbMapsList\":%d,\"maps\":[%s]}"

#define GAME_LIST_MESSAGE_STRING_PROTOTYPE "{" ACTION_MESSAGE_STRING_PROTOTYPE "," STATUT_MESSAGE_STRING_PROTOTYPE ",\"nbGamesList\":%d,\"games\":[%s]}"
#define NO_GAME_LIST_MESSAGE_STRING_PROTOTYPE "{" ACTION_MESSAGE_STRING_PROTOTYPE "," STATUT_MESSAGE_STRING_PROTOTYPE ",\"nbGamesList\":%d}"

#define GAME_CREATED_MESSAGE_STRING_PROTOTYPE "{" ACTION_MESSAGE_STRING_PROTOTYPE "," STATUT_MESSAGE_STRING_PROTOTYPE ",%s}"
#define NO_GAME_CREATED_MESSAGE_STRING_PROTOTYPE "{" ACTION_MESSAGE_STRING_PROTOTYPE "," STATUT_MESSAGE_STRING_PROTOTYPE "}"

#define JOIN_GAME_MESSAGE_STRING_PROTOTYPE "{" ACTION_MESSAGE_STRING_PROTOTYPE "," STATUT_MESSAGE_STRING_PROTOTYPE ",\"nbPlayers\":%d,\"mapId\":%d,\"players\":[%s],\"startPos\":\"%d,%d\",\"player\":%s}" 
#define NO_JOIN_GAME_MESSAGE_STRING_PROTOTYPE "{" ACTION_MESSAGE_STRING_PROTOTYPE "," STATUT_MESSAGE_STRING_PROTOTYPE "}"


#define PLAYER_UPDATE_POSITION_STRING_PROTOTYPE "POST player/position/update\n{\"player\":\"%s\",\"dir\":\"%s\"}"

#define UPDATE_POSE_BOMB_PLAYER_STRING_PROTOTYPE "{" ACTION_MESSAGE_STRING_PROTOTYPE "," STATUT_MESSAGE_STRING_PROTOTYPE ",\"player\": %s}"
#define ALERT_BOMB_POSED_STRING_PROTOTYPE "POST attack/newbomb\n{\"pos\":\"%d,%d\",\"type\":\"%s\"}"
#define ALERT_BOMB_EXPLODED_STRING_PROTOTYPE "POST attack/explose\n{\"pos\":\"%d,%d\",\"type\":\"%s\",\"impactDist\":%d,\"map\":\"%s\"}"

#define ALERT_ATTACK_AFFECT_STRING_PROTOTYPE "POST attack/affect\n%s"

#define BONUS_UPDATE_STRING_PROTOTYPE "{" ACTION_MESSAGE_STRING_PROTOTYPE STATUT_MESSAGE_STRING_PROTOTYPE ",%s}"

#define STATUT_OK 200

class JSONMessage{
private:
	int lengthNumber(int number);
public:
	JSONMessage();
	char* errorMessage(int statut, char* message);
	char* mapsListMessage(std::vector<MapJSON*> maps, int nbMaps);
	char* gamesListMessage(std::vector<GameJSON*> maps, int nbGames);
	char* gameCreatedMessage(GameJSON* game);
	char* joinGameMessage(GameJSON* game);
	char* playerPositionUpdateMessage(PlayerJSON* player, char * dir);
	char* updatePoseBombPlayerMessage(PlayerStateJSON* playerState, int posX, int posY);
	char* alertBombPosedMessage(int posX, int posY, char* type);
	char* alertBombExplodedMessage(int posX, int posY, char* type, int impactDist, char* map);
	char* alertAttackAffectMessage(PlayerStateJSON* playerState);
	char* bonusUpdateMessage(PlayerStateJSON* playerState);
	//char* 
};

#endif