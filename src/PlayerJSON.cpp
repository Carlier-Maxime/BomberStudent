#include <sstream>
#include <string>
#include "PlayerJSON.h"

PlayerJSON::PlayerJSON(std::string nameValue,int posXValue, int posYValue){
	name=nameValue;
	posX=posXValue;
	posY=posYValue;
}

std::string PlayerJSON::toJSON() const{
	std::ostringstream json;
	json << "{\"name\":\"" << this->name << "\",\"pos\":\"" << this->posY << "," << this->posX <<"\"}";

	return json.str();

}

std::string PlayerJSON::getName() const{
	return this->name;
}