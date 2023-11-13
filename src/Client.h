#ifndef BOMBER_STUDENT_CLIENT_H
#define BOMBER_STUDENT_CLIENT_H


#include "SocketUDP.h"
#include "SocketTCP.h"

class Client {
private:
    SocketAddress address;
    SocketUDP socketUDP;
    SocketTCP socketTCP;
public:
    Client();
    ~Client();
    void run();
};


#endif //BOMBER_STUDENT_CLIENT_H
