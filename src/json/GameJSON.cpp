
#include <vector>
#include <string>
#include <sstream>
#include "PlayerJSON.h"
#include "PlayerStateJSON.h"
#include "GameJSON.h"


GameJSON::GameJSON(std::string nameValue,std::vector<PlayerJSON*> playersValue, int mapIdValue,int startPosValue[], PlayerStateJSON* playerStateJSONValue){
	name=nameValue;
	players = playersValue;
	mapId=mapIdValue;
	startPos[0]=startPosValue[0];
	startPos[1]=startPosValue[1];
	playerStateJSON=playerStateJSONValue;
	
}

std::string GameJSON::toJSON() const{

	std::ostringstream json;
	json << "{\"name\":\"" << this->name << "\",\"nbPlayer\":"<< this->players.size() << ",\"mapId\":" << this->mapId << "}";
	return json.str();

}

std::string GameJSON::toDetailJSON() const{

	std::string playerJSONString = playerStateJSON->toJSON();
	std::ostringstream json;
	json << "{\"nbPlayer\":"<<this->players.size()<<",\"mapId\":"<<this->mapId<<",\"startPos\":\""<<this->startPos[0]<<","<<this->startPos[1]<<"\",\"player\":"<<playerJSONString<<"}";
	return json.str();
}

PlayerStateJSON* GameJSON::getPlayerState() const{
	return this->playerStateJSON;
}
int GameJSON::getMapId() const{
	return this->mapId;
}
int* GameJSON::getStartPos(){
	return this->startPos;
}
std::vector<PlayerJSON*> GameJSON::getPlayers() const{
	return this->players;
}