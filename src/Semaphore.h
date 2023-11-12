#ifndef BOMBER_STUDENT_SEMAPHORE_H
#define BOMBER_STUDENT_SEMAPHORE_H

#include <string>
#include "SharedMemory.h"

class Semaphore {
public:
    Semaphore(int IPCKeyID, int nb, int value);
    ~Semaphore();
    void P(unsigned short index) const;
    void V(unsigned short index) const;
    [[nodiscard]] bool isCreated() const;
private:
    int sem_id, IPCKeyID;
    SharedMemory nbProcess;
    bool created;
};


#endif //BOMBER_STUDENT_SEMAPHORE_H
