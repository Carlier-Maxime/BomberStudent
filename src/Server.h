#ifndef BOMBER_STUDENT_SERVER_H
#define BOMBER_STUDENT_SERVER_H


#include "SocketUDP.h"
#include "SocketTCP.h"

class Server {
private:
    SocketAddress address;
    SocketTCP socketTCP;
public:
    Server();
    ~Server();
    void run();

    [[noreturn]] void loopUDP();
};


#endif //BOMBER_STUDENT_SERVER_H
