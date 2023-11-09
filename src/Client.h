#ifndef BOMBER_STUDENT_CLIENT_H
#define BOMBER_STUDENT_CLIENT_H


#include "Socket.h"

class Client {
private:
    Socket socket;
public:
    Client();
    ~Client();
    void run();
};


#endif //BOMBER_STUDENT_CLIENT_H
