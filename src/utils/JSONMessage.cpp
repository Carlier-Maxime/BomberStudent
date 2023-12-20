#include <string>
#include <sstream>
#include "JSONMessage.h"
#include "ConstantMessages.h"

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
