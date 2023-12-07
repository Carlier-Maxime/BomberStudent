#ifndef BOMBER_STUDENT_CLIENT_H
#define BOMBER_STUDENT_CLIENT_H


#include "../socket/SocketUDP.h"
#include "../socket/SocketTCP.h"

class Client {
private:
    SocketUDP socketUDP;
    SocketTCP socketTCP;
    void handleReceive();
public:
    Client();
    ~Client();
    void run();
};


#endif //BOMBER_STUDENT_CLIENT_H
