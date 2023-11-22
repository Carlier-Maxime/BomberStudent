#include <string>
#include <sstream>
#include "PlayerStateJSON.h"


PlayerStateJSON::PlayerStateJSON(int lifeValue, int speedValue, int nbClassicBombValue, int nbMineValue, int nbRemoteBombValue, int impactDistValue, int invincibleValue){
	life=lifeValue;
	speed=speedValue;
	nbClassicBomb=nbClassicBombValue;
	nbMine=nbMineValue;
	nbRemoteBomb=nbRemoteBombValue;
	impactDist=impactDistValue;
	invincible=invincibleValue;
}

std::string PlayerStateJSON::toJSON() const{
	
	std::string invincibleString = this->invincible ? "True" : "False";

	std::ostringstream json;
	json << "{\"life\":"<< this->life <<",\"speed\":"<< this->speed <<",\"nbClassicBomb\":"<<this->nbClassicBomb<<",\"nbMine\":"<<this->nbMine<<",\"nbRemoteBomb\":"<<this->nbRemoteBomb<<",\"impactDist\":"<<this->impactDist<<",\"invincible\":"<<invincibleString<<"}";

	return json.str();

}