#ifndef BOMBER_STUDENT_SERVER_H
#define BOMBER_STUDENT_SERVER_H


#include <vector>
#include "../socket/SocketUDP.h"
#include "../socket/SocketTCP.h"

class Server {
private:
    SocketAddress address;
    SocketTCP socketTCP;
    std::vector<Socket> clients;
public:
    Server();
    ~Server();
    void run();
};


#endif //BOMBER_STUDENT_SERVER_H
