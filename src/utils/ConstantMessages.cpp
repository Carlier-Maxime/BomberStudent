#include "ConstantMessages.h"
#include "../json/JSONMessage.h"
#include "Config.h"

using CM = ConstantMessages;

const std::string CM::lookingServers = "looking for bomberstudent servers";
const std::string CM::serverHello = "hello i'm a bomberstudent server";
const std::string CM::getMapList = "GET maps/list";
const std::string CM::badRequest = JSONMessage::errorMessage(400, "Bad request");
const std::string CM::getGameList = "GET game/list";
const std::string CM::postGameCreate = "POST game/create";
const std::string CM::failedCreateGame = JSONMessage::actionMessage("game/create", 501, "cannot create game", "");
const std::string CM::postGameJoin = "POST game/join";
const std::string CM::failedJoinGame = JSONMessage::actionMessage("game/join", 501, "cannot join the game", "");
const std::string CM::postGameStart = "POST game/start";
const std::string CM::postGameReady = "POST game/ready\n{\"time\":"+std::to_string(Config::getGameReadyTime())+"}";
const std::string CM::postGameGo = "POST game/go";
const std::string CM::postPlayerMove = "POST player/move";
const std::string CM::postAttackBomb = "POST attack/bomb";
const std::string CM::postAttackNewBomb = "POST attack/newbomb";
const std::string CM::postAttackExplode = "POST attack/explose";
const std::string CM::postAttackAffect = "POST attack/affect";
const std::string CM::postPlayerNew = "POST player/new";
const std::string CM::postAttackRemoteGo = "POST attack/remote/go";
const std::string CM::postPlayerLeave = "POST player/leave";
const std::string CM::postPlayerDeath = "POST player/death";
const std::string CM::postObjectGet = "POST object/get";
const std::string CM::postObjectDel = "POST object/del";