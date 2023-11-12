#ifndef BOMBER_STUDENT_CLIENT_H
#define BOMBER_STUDENT_CLIENT_H


#include "SocketUDP.h"

class Client {
private:
    SocketUDP socket;
public:
    Client();
    ~Client();
    void run();
};


#endif //BOMBER_STUDENT_CLIENT_H
