#ifndef BOMBER_STUDENT_MUTEX_H
#define BOMBER_STUDENT_MUTEX_H

#include "Semaphore.h"

class Mutex {
public:
    explicit Mutex(int IPCKeyID, bool isDynamic);
    ~Mutex();
    void P();
    void V();
    bool isCreated();
private:
    Semaphore* sem;
    bool isDynamic;
};


#endif //BOMBER_STUDENT_MUTEX_H
