#include "ConstantMessages.h"
#include "../json/JSONMessage.h"

const std::string ConstantMessages::lookingServers = "looking for bomberstudent servers";
const std::string ConstantMessages::serverHello = "hello i’m a bomberstudent server";
const std::string ConstantMessages::getMapList = "GET maps/list";
const std::string ConstantMessages::badRequest = JSONMessage::errorMessage(400, "Bad request");
const std::string ConstantMessages::getGameList = "GET game/list";
const std::string ConstantMessages::postGameCreate = "POST game/create";
const std::string ConstantMessages::failedCreateGame = JSONMessage::actionMessage("game/create", 501, "cannot create game", "");
const std::string ConstantMessages::postGameJoin = "POST game/join";
const std::string ConstantMessages::failedJoinGame = JSONMessage::actionMessage("game/join", 501, "cannot join the game", "");
const std::string ConstantMessages::postGameStart = "POST game/start";
const std::string ConstantMessages::postGameReady = "POST game/ready\n{\"time\":3}";
const std::string ConstantMessages::postGameGo = "POST game/go";