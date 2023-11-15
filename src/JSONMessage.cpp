#include <vector>
#include "PlayerStateJSON.h"
#include "PlayerJSON.h"
#include "GameJSON.h"
#include "MapJSON.h"
#include "JSONMessage.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



JSONMessage::JSONMessage(){}

char* JSONMessage::errorMessage(int statut, char* message){

	int length = strlen(STATUT_MESSAGE_STRING_PROTOTYPE)+strlen(message)+this->lengthNumber(statut)+2;
	char* errorMessage = new char[length];
	sprintf(errorMessage, "{" STATUT_MESSAGE_STRING_PROTOTYPE "}", statut,message );
	return errorMessage;
}

char* JSONMessage::mapsListMessage(std::vector<MapJSON*> maps, int nbMaps){
	const char* action = "maps/list";
	if(nbMaps==0) return (char*) -1;
	char** mapsJSONString = new char*[nbMaps];

	int mapsLength = nbMaps-1;
	for(int i=0;i<nbMaps;i++){
		mapsJSONString[i]=maps.at(i)->toJSON();
		mapsLength+=strlen(mapsJSONString[i]);
	}
	char* allMapString = new char[mapsLength];
	int idx=0;
	for(int i =0 ;i<nbMaps;i++){
		if(i>0) allMapString[idx++]=',';
		int length = strlen(mapsJSONString[i]);
		for(int j=0;j<length;j++){
			allMapString[idx++]=mapsJSONString[i][j];
		}
		delete [] mapsJSONString[i];
	}
	delete[] mapsJSONString;
	int totalLength=mapsLength+strlen(action)+this->lengthNumber(STATUT_OK)+strlen(MAP_LIST_MESSAGE_STRING_PROTOTYPE);
	char * res = new char[totalLength];
	sprintf(res,MAP_LIST_MESSAGE_STRING_PROTOTYPE,action,STATUT_OK,"ok",nbMaps,allMapString);
	delete [] allMapString;
	return res;
}
char* JSONMessage::gamesListMessage(std::vector<GameJSON*> games, int nbGames){
	const char* action = "game/list";
	char** gamesJSONString = new char*[nbGames];

	if(nbGames>0){
		int gamesLength = nbGames-1;
		for(int i=0;i<nbGames;i++){
			gamesJSONString[i]=games.at(i)->toJSON();
			gamesLength+=strlen(gamesJSONString[i]);
		}
		char* allGameString = new char[gamesLength];
		int idx=0;
		for(int i =0 ;i<nbGames;i++){
			if(i>0) allGameString[idx++]=',';
			int length = strlen(gamesJSONString[i]);
			for(int j=0;j<length;j++){
				allGameString[idx++]=gamesJSONString[i][j];
			}
			delete [] gamesJSONString[i];
		}
		delete [] gamesJSONString;
		int totalLength=gamesLength+strlen(action)+this->lengthNumber(STATUT_OK)+strlen(GAME_LIST_MESSAGE_STRING_PROTOTYPE);
		char * res = new char[totalLength];
		sprintf(res,GAME_LIST_MESSAGE_STRING_PROTOTYPE,action,STATUT_OK,"ok",nbGames,allGameString);
		delete [] allGameString;
		return res;
	}else{
		int totalLength=strlen(action)+this->lengthNumber(STATUT_OK)+strlen(NO_GAME_LIST_MESSAGE_STRING_PROTOTYPE);
		char * res = new char[totalLength];
		sprintf(res,NO_GAME_LIST_MESSAGE_STRING_PROTOTYPE,action,STATUT_OK,"ok",nbGames);
		return res;
	}
	
}

char* JSONMessage::gameCreatedMessage(GameJSON* game){
	const char* action = "game/create"; 
	if(game==NULL){
		const char* msg = "cannot create game";
		int statut = 501;
		int totalLength=strlen(NO_GAME_CREATED_MESSAGE_STRING_PROTOTYPE)+strlen(action)+strlen(msg)+lengthNumber(statut);
		char* json = new char[totalLength];
		sprintf(json, NO_GAME_CREATED_MESSAGE_STRING_PROTOTYPE, action,statut,msg);
		return json;
	}
	const char* msg = "game created";
	int statut = 201;
	char* gameDetailJSON = game->toDetailJSON();
	int gameDetailLength = strlen(gameDetailJSON);
	gameDetailJSON[gameDetailLength-1]='\0';
	gameDetailLength-=2;
	int totalLength=strlen(GAME_CREATED_MESSAGE_STRING_PROTOTYPE)+strlen(action)+strlen(msg)+lengthNumber(statut)+gameDetailLength;
	char* json = new char[totalLength];
	sprintf(json,GAME_CREATED_MESSAGE_STRING_PROTOTYPE,action,statut,msg, gameDetailJSON+1);
	delete [] gameDetailJSON;
	return json;
}

char* JSONMessage::joinGameMessage(GameJSON* game){
	const char* action = "game/join";
	if(game==NULL){
		const char* msg = "cannot join game";
		int statut = 501;
		int totalLength=strlen(NO_JOIN_GAME_MESSAGE_STRING_PROTOTYPE)+strlen(action)+strlen(msg)+lengthNumber(statut);
		char* json = new char[totalLength];
		sprintf(json, NO_JOIN_GAME_MESSAGE_STRING_PROTOTYPE, action,statut,msg);
		return json;
	}
	std::vector<PlayerJSON*> players = game->getPlayers();
	int nbPlayers = players.size();
	int statut = 201;
	const char* msg = "game joined";
	int mapId=game->getMapId();
	int * startPos=game->getStartPos();


	char** playerJSONString = new char*[nbPlayers];
	int playersLength = nbPlayers-1;
	for(int i=0;i<nbPlayers;i++){
		playerJSONString[i]=players.at(i)->toJSON();
		playersLength+=strlen(playerJSONString[i]);
	}
	char* allPlayerString = new char[playersLength+1];
	int idx=0;
	for(int i =0 ;i<nbPlayers;i++){
		if(i>0) allPlayerString[idx++]=',';
		int length = strlen(playerJSONString[i]);
		for(int j=0;j<length;j++){
			allPlayerString[idx++]=playerJSONString[i][j];
		}
		delete [] playerJSONString[i];
	}
	allPlayerString[playersLength]='\0';
	delete [] playerJSONString;
	char* playerState = game->getPlayerState()->toJSON();
	int totalLength = strlen(JOIN_GAME_MESSAGE_STRING_PROTOTYPE)+this->lengthNumber(statut)+strlen(action)+strlen(msg)+strlen(allPlayerString)+this->lengthNumber(nbPlayers)+this->lengthNumber(startPos[0])+this->lengthNumber(startPos[1])+strlen(playerState);
	char* json = new char[totalLength];
	sprintf(json, JOIN_GAME_MESSAGE_STRING_PROTOTYPE, action, statut,msg,nbPlayers, mapId, allPlayerString,startPos[0],startPos[1],playerState);
	delete [] playerState;
	delete [] allPlayerString;
	return json;


}

char* JSONMessage::playerPositionUpdateMessage(PlayerJSON* player, char* dir){
	char* name = player->getName();
	int totalLength = strlen(PLAYER_UPDATE_POSITION_STRING_PROTOTYPE)+strlen(name)+strlen(dir);
	char* message = new char[totalLength];
	sprintf(message, PLAYER_UPDATE_POSITION_STRING_PROTOTYPE, name, dir); 
	return(message);
}

char* JSONMessage::updatePoseBombPlayerMessage(PlayerStateJSON* playerState, int posX, int posY){
	const char* action = "attack/bomb";
	int statut = 201;
	int lengthMsg = strlen("bomb is armed at pos %d,%d")+this->lengthNumber(posX)+this->lengthNumber(posY);
	char* msg = new char[lengthMsg];
	sprintf(msg, "bomb is armed at pos %d,%d",posY,posX);
	char* playerStateJSONString = playerState->toJSON();
	int totalLength = strlen(UPDATE_POSE_BOMB_PLAYER_STRING_PROTOTYPE)+this->lengthNumber(statut)+strlen(action)+lengthMsg+strlen(playerStateJSONString);
	char* json = new char[totalLength];

	sprintf(json,UPDATE_POSE_BOMB_PLAYER_STRING_PROTOTYPE,action,statut,msg,playerStateJSONString);
	delete [] msg;
	delete [] playerStateJSONString;
	return json;

}
char* JSONMessage::alertBombPosedMessage(int posX, int posY, char* type){
	int totalLength=strlen(ALERT_BOMB_POSED_STRING_PROTOTYPE)+this->lengthNumber(posX)+this->lengthNumber(posY)+strlen(type);
	char* json = new char[totalLength];
	sprintf(json, ALERT_BOMB_POSED_STRING_PROTOTYPE,posY,posX,type);
	return json;
}

char* JSONMessage::alertBombExplodedMessage(int posX, int posY, char* type, int impactDist, char* map){
	int totalLength=strlen(ALERT_BOMB_EXPLODED_STRING_PROTOTYPE)+this->lengthNumber(posX)+this->lengthNumber(posY)+this->lengthNumber(impactDist)+strlen(type)+strlen(map);
	char* json = new char[totalLength];
	sprintf(json, ALERT_BOMB_EXPLODED_STRING_PROTOTYPE,posY,posX,type,impactDist,map);
	return json;
}

char* JSONMessage::alertAttackAffectMessage(PlayerStateJSON* playerState){
	char* playerStateJSONString = playerState->toJSON();
	int totalLength=strlen(ALERT_ATTACK_AFFECT_STRING_PROTOTYPE)+strlen(playerStateJSONString);
	char* json = new char[totalLength];
	sprintf(json,ALERT_ATTACK_AFFECT_STRING_PROTOTYPE,playerStateJSONString);
	delete [] playerStateJSONString;
	return json;
}
char* JSONMessage::bonusUpdateMessage(PlayerStateJSON* playerState){
	const char* action = "object/new";
	const char* msg="ok";
	int statut = 201;
	char* playerStateJSONString = playerState->toJSON();
	int playerStateLength = strlen(playerStateJSONString);
	playerStateJSONString[playerStateLength-1]='\0';
	int totalLength=strlen(BONUS_UPDATE_STRING_PROTOTYPE)+(playerStateLength-2)+strlen(action)+strlen(msg)+this->lengthNumber(statut);
	char* json = new char[totalLength];
	sprintf(json,BONUS_UPDATE_STRING_PROTOTYPE,action,statut,msg,playerStateJSONString+1);
	delete [] playerStateJSONString;
	return json;	
}

int JSONMessage::lengthNumber(int number){
	int tmp=number;
	int length = 0;
	while(tmp>9){
		tmp=tmp/10;
		length+=1;
	}
	return length;
}
