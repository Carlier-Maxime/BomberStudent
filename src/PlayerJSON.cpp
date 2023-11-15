#include "PlayerJSON.h"
#include <string.h>
#include <stdio.h>

PlayerJSON::PlayerJSON(char* nameValue,int posXValue, int posYValue){
	name=nameValue;
	posX=posXValue;
	posY=posYValue;
}

char* PlayerJSON::toJSON(){
	int lengthPosX = 1;
	int tmp=posX;
	while(tmp>9){
		tmp=tmp/10;
		lengthPosX+=1;
	}
	int lengthPosY = 1;
	tmp=posY;
	while(tmp>9){
		tmp=tmp/10;
		lengthPosY+=1;
	}
	int lengthName = strlen(name);
	int totalLength=strlen(PLAYER_JSON_STRING_PROTOTYPE)+lengthName+lengthPosX+lengthPosY+1;
	char* json = new char[totalLength];
	sprintf(json,PLAYER_JSON_STRING_PROTOTYPE,name,posY,posX);
	return json;

}

char* PlayerJSON::getName(){
	return this->name;
}