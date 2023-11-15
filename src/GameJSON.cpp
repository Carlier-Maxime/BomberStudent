
#include <vector>
#include "PlayerJSON.h"
#include "PlayerStateJSON.h"
#include "GameJSON.h"
#include <string.h>
#include <stdio.h>
#include <cstdlib>


GameJSON::GameJSON(char* nameValue,int nbPlayerValue, int mapIdValue){
	name=nameValue;
	nbPlayer = nbPlayerValue;
	mapId=mapIdValue;
}
GameJSON::GameJSON(char* nameValue,std::vector<PlayerJSON*> playersValue, int mapIdValue,int startPosValue[], PlayerStateJSON* playerStateJSONValue){
	name=nameValue;
	players = playersValue;
	mapId=mapIdValue;
	startPos[0]=startPosValue[0];
	startPos[1]=startPosValue[1];
	playerStateJSON=playerStateJSONValue;
	
}

char* GameJSON::toJSON(){
	int lengthNbPlayer = 1;
	int tmp=nbPlayer;
	while(tmp>9){
		tmp=tmp/10;
		lengthNbPlayer+=1;
	}
	int lengthMapId = 1;
	tmp=mapId;
	while(tmp>9){
		tmp=tmp/10;
		lengthMapId+=1;
	}
	int lengthName = strlen(name);
	int totalLength=strlen(GAME_JSON_STRING_PROTOTYPE)+lengthMapId+lengthName+lengthNbPlayer;
	char* json = new char[totalLength];
	sprintf(json,GAME_JSON_STRING_PROTOTYPE,name,nbPlayer,mapId);
	return json;

}

char* GameJSON::toDetailJSON(){
	int nbPlayer = this->players.size();
	int lengthNbPlayer = 1;
	int tmp=nbPlayer;
	while(tmp>9){
		tmp=tmp/10;
		lengthNbPlayer+=1;
	}
	int lengthMapId = 1;
	tmp=mapId;
	while(tmp>9){
		tmp=tmp/10;
		lengthMapId+=1;
	}
	int lengthPosY = 1;
	tmp=startPos[0];
	while(tmp>9){
		tmp=tmp/10;
		lengthPosY+=1;
	}
	int lengthPosX = 1;
	tmp=startPos[1];
	while(tmp>9){
		tmp=tmp/10;
		lengthPosX+=1;
	}
	char* playerJSONString = playerStateJSON->toJSON();
	int totalLength=lengthNbPlayer+lengthMapId+lengthPosX+lengthPosY+strlen(playerJSONString)+strlen(GAME_JSON_DETAIL_STRING_PROTOTYPE)+1;
	char * json = new char[totalLength];
	sprintf(json,GAME_JSON_DETAIL_STRING_PROTOTYPE,nbPlayer,mapId,startPos[0],startPos[1],playerJSONString);
	delete [] playerJSONString;
	return json;
}

PlayerStateJSON* GameJSON::getPlayerState(){
	return this->playerStateJSON;
}
int GameJSON::getMapId(){
	return this->mapId;
}
int* GameJSON::getStartPos(){
	return this->startPos;
}
std::vector<PlayerJSON*> GameJSON::getPlayers(){
	return this->players;
}