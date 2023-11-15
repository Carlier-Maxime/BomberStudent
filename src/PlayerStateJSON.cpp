#include "PlayerStateJSON.h"
#include <string.h>
#include <stdio.h>

PlayerStateJSON::PlayerStateJSON(int lifeValue, int speedValue, int nbClassicBombValue, int nbMineValue, int nbRemoteBombValue, int impactDistValue, int invincibleValue){
	life=lifeValue;
	speed=speedValue;
	nbClassicBomb=nbClassicBombValue;
	nbMine=nbMineValue;
	nbRemoteBomb=nbRemoteBombValue;
	impactDist=impactDistValue;
	invincible=invincibleValue;
}

char* PlayerStateJSON::toJSON(){
	int lengthLife = 1;
	int tmp=life;
	while(tmp>9){
		tmp=tmp/10;
		lengthLife+=1;
	}
	int lengthSpeed = 1;
	tmp=speed;
	while(tmp>9){
		tmp=tmp/10;
		lengthSpeed+=1;
	}
	int lengthNbClassicBomb = 1;
	tmp=nbClassicBomb;
	while(tmp>9){
		tmp=tmp/10;
		lengthNbClassicBomb+=1;
	}

	int lengthNbMine = 1;
	tmp=nbMine;
	while(tmp>9){
		tmp=tmp/10;
		lengthNbMine+=1;
	}

	int lengthNbRemoteBomb = 1;
	tmp=nbRemoteBomb;
	while(tmp>9){
		tmp=tmp/10;
		lengthNbRemoteBomb+=1;
	}

	int lengthImpactDist = 1;
	tmp=impactDist;
	while(tmp>9){
		tmp=tmp/10;
		lengthImpactDist+=1;
	}
	const char* invincibleString = invincible ? "True" : "False";
	int lengthInvincible=strlen(invincibleString);


	int totalLength=strlen(PLAYER_STATE_JSON_STRING_PROTOTYPE)+lengthLife+lengthSpeed+lengthNbClassicBomb+lengthNbMine+lengthNbRemoteBomb+lengthImpactDist+lengthInvincible;
	char* json = new char[totalLength];
	sprintf(json,PLAYER_STATE_JSON_STRING_PROTOTYPE,life,speed,nbClassicBomb,nbMine,nbRemoteBomb,impactDist,invincibleString);
	return json;

}