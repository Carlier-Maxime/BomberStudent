#ifndef BOMBER_STUDENT_SERVER_H
#define BOMBER_STUDENT_SERVER_H


#include "SocketUDP.h"

class Server {
private:
    SocketUDP socket;
public:
    Server();
    ~Server();
    void run();
};


#endif //BOMBER_STUDENT_SERVER_H
