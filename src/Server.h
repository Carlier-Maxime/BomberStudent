#ifndef BOMBER_STUDENT_SERVER_H
#define BOMBER_STUDENT_SERVER_H


#include "SocketUDP.h"
#include "SocketTCP.h"

class Server {
private:
    SocketAddress address;
    SocketUDP socketUDP;
    SocketTCP socketTCP;
public:
    Server();
    ~Server();
    void run();
    void loopUDP();
};


#endif //BOMBER_STUDENT_SERVER_H
