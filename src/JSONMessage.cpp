#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include "PlayerStateJSON.h"
#include "PlayerJSON.h"
#include "GameJSON.h"
#include "MapJSON.h"
#include "JSONMessage.h"



JSONMessage::JSONMessage(){}

std::string JSONMessage::errorMessage(int statut, std::string message) const{

	std::ostringstream errorMessage;
	errorMessage << "{\"statut\":"<<statut<<",\"message\":\""<<message<<"\"}";
	return errorMessage.str();
}

std::string JSONMessage::mapsListMessage(std::vector<MapJSON*> maps, int nbMaps) const{
	if(nbMaps==0) return "error";
	std::ostringstream res;
	std::ostringstream allMapString;
	std::string action = "maps/list";
	
	
	for(int i =0 ;i<nbMaps;i++){
		if(i>0) allMapString << ",";
		allMapString << maps.at(i)->toJSON();
	}
	
	res << "{\"action\":\"" << action << "\", \"statut\":200,\"message\":\"ok\",\"nbMapsList\":" << nbMaps << ",\"maps\":[" << allMapString.str() << "]}";
	return res.str();
}

std::string JSONMessage::gamesListMessage(std::vector<GameJSON*> games, int nbGames) const{
	std::string action = "game/list";

	if(nbGames>0){
		std::ostringstream allGameString;
		for(int i =0 ;i<nbGames;i++){
			if(i>0) allGameString << ",";
			
			allGameString << games.at(i)->toJSON();
		}
		std::ostringstream res;
		res << "{\"action\":\"" << action << "\", \"statut\":200,\"message\":\"ok\",\"nbGamesList\":"<<nbGames<<"\"games\":[" << allGameString.str() <<"]}";
		return res.str();
	}else{
		std::ostringstream res;
		res << "{\"action\":\"" << action << "\", \"statut\":200,\"message\":\"ok\",\"nbGamesList\":"<<nbGames<<"}";
		return res.str();
	}
	
}

std::string JSONMessage::gameCreatedMessage(GameJSON* game) const{
	std::string action = "game/create"; 
	if(game==nullptr){
		std::string msg = "cannot create game";
		std::ostringstream json;
		json << "{\"action\":\"" << action << "\",\"statut\":501,\"message\":\"" << msg << "\"}";

		return json.str();
	}
	std::string msg = "game created";
	std::string gameJSONString = game->toDetailJSON();
	std::ostringstream json;
	json << "{\"action\":\"" << action << "\",\"statut\":201,\"message\":\"" << msg << "\"," << gameJSONString.substr(1,gameJSONString.size()-2)<<"}" ;
		
	return json.str();
}

std::string JSONMessage::joinGameMessage(GameJSON* game) const{
	std::string action = "game/join";
	if(game==nullptr){
		std::string msg = "cannot join game";
		int statut = 501;
		std::ostringstream json;
		json << "{\"action\":\""<< action <<"\",\"statut\":\"" << statut << "\",\"message\":\"" << msg << "\"}";
		return json.str();
	}
	std::vector<PlayerJSON*> players = game->getPlayers();
	int nbPlayers = players.size();
	int statut = 201;
	std::string msg = "game joined";
	int mapId=game->getMapId();
	int * startPos=game->getStartPos();

	std::ostringstream allPlayerString;
	for(int i =0 ;i<nbPlayers;i++){
		if(i>0) allPlayerString << ",";
		allPlayerString << players.at(i)->toJSON();
	}
	std::string playerState = game->getPlayerState()->toJSON();
	std::ostringstream json;
	json << "{\"action\":\""<< action <<"\"" "," "\"statut\":\""<<  statut<<"\",\"message\":\""<< msg <<"\"" ",\"nbPlayers\":"<< nbPlayers <<",\"mapId\":"<< mapId <<",\"players\":[" <<  allPlayerString.str() << "],\"startPos\":\""<< startPos[0] <<"," << startPos[1] <<"\",\"player\":" << playerState << "}" ; 
	return json.str();


}

std::string JSONMessage::playerPositionUpdateMessage(PlayerJSON* player, std::string dir) const{
	std::string name = player->getName();
	std::ostringstream message;
	message << "POST player/position/update\n{\"player\":\""<< name << "\",\"dir\":\""<< dir <<"\"}";
	return message.str();
}

std::string JSONMessage::updatePoseBombPlayerMessage(PlayerStateJSON* playerState, int posX, int posY) const{
	std::string action = "attack/bomb";
	int statut = 201;
	std::ostringstream msg;
	msg << "bomb is armed at pos " << posY << "," << posX;
	std::string playerStateJSONString = playerState->toJSON();
	std::ostringstream json;
	json << "{\"action\":\""<< action <<"\",\"statut\":\"" << statut << "\",\"message\":\""<< msg.str() <<"\",\"player\": "<< playerStateJSONString <<"}";

	return json.str();

}
std::string JSONMessage::alertBombPosedMessage(int posX, int posY, std::string type) const{
	std::ostringstream json;
	json << "POST attack/newbomb\n{\"pos\":\""<< posY << ","<< posX << "\",\"type\":\""<< type <<"\"}";
	return json.str();
}

std::string JSONMessage::alertBombExplodedMessage(int posX, int posY, std::string type, int impactDist, std::string map) const{
	std::ostringstream json;
	json <<  "POST attack/explose\n{\"pos\":\""<< posY <<","<< posX <<"\",\"type\":\""<< type <<"\",\"impactDist\":"<< impactDist << ",\"map\":\""<< map <<"\"}"; 

	return json.str();
}

std::string JSONMessage::alertAttackAffectMessage(PlayerStateJSON* playerState) const{
	std::string playerStateJSONString = playerState->toJSON();
	
	std::ostringstream json;
	json << "POST attack/affect\n" << playerStateJSONString;
	return json.str();
}
std::string JSONMessage::bonusUpdateMessage(PlayerStateJSON* playerState) const{
	std::string action = "object/new";
	std::string msg="ok";
	int statut = 201;
	std::string playerStateJSONString = playerState->toJSON();
	playerStateJSONString = playerStateJSONString.substr(1, playerStateJSONString.size()-2);

	std::ostringstream json;
	json << "{\"action\":\"" << action << "\",\"statut\":" << statut << ",\"message\":\"" << msg << "\"," << playerStateJSONString << "}";

	return json.str();	
}

