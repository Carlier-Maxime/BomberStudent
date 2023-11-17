
#include <sstream>
#include <cstring>
#include <cstdio>
#include <string>
#include "MapJSON.h"

MapJSON::MapJSON(int idValue, int widthValue, int heightValue, std::string contentValue){
	id=idValue;
	width = widthValue;
	height=heightValue;
	content=contentValue;
}

std::string MapJSON::toJSON() const{

	std::ostringstream json;
	json << "{\"id\":" << this->id << ",\"width\":" << this->width << ",\"height\":" << this->height << ",\"content\":\"" << this->content << "\"}";

	return json.str();

}