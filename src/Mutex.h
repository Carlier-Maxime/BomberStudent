#ifndef BOMBER_STUDENT_MUTEX_H
#define BOMBER_STUDENT_MUTEX_H

#include "Semaphore.h"

class Mutex : public Semaphore {
public:
    explicit Mutex(int IPCKeyID);
    ~Mutex();
    void P();
    void V();
};


#endif //BOMBER_STUDENT_MUTEX_H
