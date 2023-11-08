#ifndef BOMBER_STUDENT_SERVER_H
#define BOMBER_STUDENT_SERVER_H


#include "Socket.h"

class Server {
private:
    Socket socket;
public:
    Server();
    ~Server();
    void run();
};


#endif //BOMBER_STUDENT_SERVER_H
