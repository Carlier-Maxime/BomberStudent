#include <vector>
#include <string>
#include <sstream>
#include "PlayerStateJSON.h"
#include "PlayerJSON.h"
#include "GameJSON.h"
#include "MapJSON.h"
#include "JSONMessage.h"


std::string JSONMessage::errorMessage(int statut, const std::string& message) {
	std::ostringstream errorMessage;
	errorMessage << "{\"statut\":"<<statut<<R"(,"message":")"<<message<<"\"}";
	return errorMessage.str();
}

std::string JSONMessage::mapsListMessage(std::vector<MapJSON*> maps, int nbMaps) {
	if(nbMaps==0) return "error";
	std::ostringstream res;
	std::ostringstream allMapString;
	std::string action = "maps/list";
	
	
	for(int i =0 ;i<nbMaps;i++){
		if(i>0) allMapString << ",";
		allMapString << maps.at(i)->toJSON();
	}
	
	res << R"({"action":")" << action << R"(", "statut":200,"message":"ok","nbMapsList":)" << nbMaps << ",\"maps\":[" << allMapString.str() << "]}";
	return res.str();
}

std::string JSONMessage::gamesListMessage(std::vector<GameJSON*> games, int nbGames) {
	std::string action = "game/list";

	if(nbGames>0){
		std::ostringstream allGameString;
		for(int i =0 ;i<nbGames;i++){
			if(i>0) allGameString << ",";
			
			allGameString << games.at(i)->toJSON();
		}
		std::ostringstream res;
		res << R"({"action":")" << action << R"(", "statut":200,"message":"ok","nbGamesList":)"<<nbGames<<"\"games\":[" << allGameString.str() <<"]}";
		return res.str();
	}else{
		std::ostringstream res;
		res << R"({"action":")" << action << R"(", "statut":200,"message":"ok","nbGamesList":)"<<nbGames<<"}";
		return res.str();
	}
	
}

std::string JSONMessage::gameCreatedMessage(GameJSON* game) {
	std::string action = "game/create"; 
	if(game==nullptr){
		std::string msg = "cannot create game";
		std::ostringstream json;
		json << R"({"action":")" << action << R"(","statut":501,"message":")" << msg << "\"}";

		return json.str();
	}
	std::string msg = "game created";
	std::string gameJSONString = game->toDetailJSON();
	std::ostringstream json;
	json << R"({"action":")" << action << R"(","statut":201,"message":")" << msg << "\"," << gameJSONString.substr(1,gameJSONString.size()-2)<<"}" ;
		
	return json.str();
}

std::string JSONMessage::joinGameMessage(GameJSON* game) {
	std::string action = "game/join";
	if(game==nullptr){
		std::string msg = "cannot join game";
		int statut = 501;
		std::ostringstream json;
		json << R"({"action":")"<< action <<R"(","statut":")" << statut << R"(","message":")" << msg << "\"}";
		return json.str();
	}
	std::vector<PlayerJSON*> players = game->getPlayers();
	u_int nbPlayers = players.size();
	int statut = 201;
	std::string msg = "game joined";
	int mapId=game->getMapId();
	int * startPos=game->getStartPos();

	std::ostringstream allPlayerString;
	for(u_int i =0 ;i<nbPlayers;i++){
		if(i>0) allPlayerString << ",";
		allPlayerString << players.at(i)->toJSON();
	}
	std::string playerState = game->getPlayerState()->toJSON();
	std::ostringstream json;
	json << R"({"action":")"<< action <<"\"" "," "\"statut\":\""<<  statut<<R"(","message":")"<< msg <<"\"" ",\"nbPlayers\":"<< nbPlayers <<",\"mapId\":"<< mapId <<",\"players\":[" <<  allPlayerString.str() << R"(],"startPos":")"<< startPos[0] <<"," << startPos[1] <<R"(","player":)" << playerState << "}" ;
	return json.str();


}

std::string JSONMessage::playerPositionUpdateMessage(PlayerJSON* player, const std::string& dir) {
	std::string name = player->getName();
	std::ostringstream message;
	message << "POST player/position/update\n{\"player\":\""<< name << R"(","dir":")"<< dir <<"\"}";
	return message.str();
}

std::string JSONMessage::updatePoseBombPlayerMessage(PlayerStateJSON* playerState, int posX, int posY) {
	std::string action = "attack/bomb";
	int statut = 201;
	std::ostringstream msg;
	msg << "bomb is armed at pos " << posY << "," << posX;
	std::string playerStateJSONString = playerState->toJSON();
	std::ostringstream json;
	json << R"({"action":")"<< action <<R"(","statut":")" << statut << R"(","message":")"<< msg.str() <<R"(","player": )"<< playerStateJSONString <<"}";

	return json.str();

}
std::string JSONMessage::alertBombPosedMessage(int posX, int posY, const std::string& type) {
	std::ostringstream json;
	json << "POST attack/newbomb\n{\"pos\":\""<< posY << ","<< posX << R"(","type":")"<< type <<"\"}";
	return json.str();
}

std::string JSONMessage::alertBombExplodedMessage(int posX, int posY, const std::string& type, int impactDist, const std::string& map) {
	std::ostringstream json;
	json <<  "POST attack/explose\n{\"pos\":\""<< posY <<","<< posX <<R"(","type":")"<< type <<R"(","impactDist":)"<< impactDist << R"(,"map":")"<< map <<"\"}";

	return json.str();
}

std::string JSONMessage::alertAttackAffectMessage(PlayerStateJSON* playerState) {
	std::string playerStateJSONString = playerState->toJSON();
	
	std::ostringstream json;
	json << "POST attack/affect\n" << playerStateJSONString;
	return json.str();
}
std::string JSONMessage::bonusUpdateMessage(PlayerStateJSON* playerState) {
	std::string action = "object/new";
	std::string msg="ok";
	int statut = 201;
	std::string playerStateJSONString = playerState->toJSON();
	playerStateJSONString = playerStateJSONString.substr(1, playerStateJSONString.size()-2);

	std::ostringstream json;
	json << R"({"action":")" << action << R"(","statut":)" << statut << R"(,"message":")" << msg << "\"," << playerStateJSONString << "}";

	return json.str();	
}

