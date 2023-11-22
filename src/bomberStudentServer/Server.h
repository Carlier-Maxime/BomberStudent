#ifndef BOMBER_STUDENT_SERVER_H
#define BOMBER_STUDENT_SERVER_H


#include "../socket/SocketUDP.h"
#include "../socket/SocketTCP.h"

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
