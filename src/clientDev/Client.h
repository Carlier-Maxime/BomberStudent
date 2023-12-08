#ifndef BOMBER_STUDENT_CLIENT_H
#define BOMBER_STUDENT_CLIENT_H


#include <condition_variable>
#include "../socket/SocketUDP.h"
#include "../socket/SocketTCP.h"

class Client {
private:
    bool gameStarted;
    std::condition_variable cv_gameStarted;
    std::mutex mutex;
    SocketUDP socketUDP;
    SocketTCP socketTCP;
    void handleReceive();
public:
    Client();
    ~Client();
    void run();
};


#endif //BOMBER_STUDENT_CLIENT_H
