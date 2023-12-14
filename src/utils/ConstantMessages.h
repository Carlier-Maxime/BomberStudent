#ifndef BOMBER_STUDENT_CONSTANT_MESSAGES_H
#define BOMBER_STUDENT_CONSTANT_MESSAGES_H


#include <string>

class ConstantMessages {
public:
    static const std::string lookingServers;
    static const std::string serverHello;
    static const std::string getMapList;
    static const std::string badRequest;
    static const std::string getGameList;
    static const std::string postGameCreate;
    static const std::string failedCreateGame;
    static const std::string postGameJoin;
    static const std::string failedJoinGame;
    static const std::string postGameStart;
    static const std::string postGameReady;
    static const std::string postGameGo;
    static const std::string postPlayerMove;
    static const std::string postAttackBomb;
    static const std::string postAttackNewBomb;
    static const std::string postAttackExplode;
};


#endif //BOMBER_STUDENT_CONSTANT_MESSAGES_H
