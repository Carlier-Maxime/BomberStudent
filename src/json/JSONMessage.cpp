#include <string>
#include <sstream>
#include "JSONMessage.h"
#include "../utils/ConstantMessages.h"

using CM = ConstantMessages;

std::string JSONMessage::errorMessage(int statut, const std::string& message) {
	std::ostringstream errorMessage;
	errorMessage << "{\"statut\":"<<statut<<R"(,"message":")"<<message<<"\"}";
	return errorMessage.str();
}

std::string JSONMessage::actionMessage(const std::string& action, int statut, const std::string& message, const std::string& jsonContent) {
    std::ostringstream json;
    json << R"({"action":")" << action << R"(","statut":)" << statut << R"(,"message":")" << message << (jsonContent.empty() ? "\"" : "\",") << jsonContent << '}';
    return json.str();
}

std::string JSONMessage::bonusUpdateMessage(Player* playerState) {
	std::string action = "object/new";
	std::string msg="ok";
	int statut = 201;
	std::string playerStateJSONString = playerState->toJSON();
	playerStateJSONString = playerStateJSONString.substr(1, playerStateJSONString.size()-2);

	std::ostringstream json;
	json << R"({"action":")" << action << R"(","statut":)" << statut << R"(,"message":")" << msg << "\"," << playerStateJSONString << "}";

	return json.str();	
}

