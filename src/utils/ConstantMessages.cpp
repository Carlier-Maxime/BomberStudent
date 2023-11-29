#include "ConstantMessages.h"
#include "../json/JSONMessage.h"

const std::string ConstantMessages::lookingServers = "looking for bomberstudent servers";
const std::string ConstantMessages::serverHello = "hello i’m a bomberstudent server";
const std::string ConstantMessages::getMapList = "GET maps/list";
const std::string ConstantMessages::badRequest = JSONMessage::errorMessage(400, "Bad request");
const std::string ConstantMessages::getGameList = "GET game/list";