#ifndef BOMBER_STUDENT_SEMAPHORE_DYNAMIC_H
#define BOMBER_STUDENT_SEMAPHORE_DYNAMIC_H

#include "Semaphore.h"
#include "SharedMemory.h"

class SemaphoreDynamic : public Semaphore {
public:
    SemaphoreDynamic(int IPCKeyID, int nb, int value);
    ~SemaphoreDynamic();
    void P(unsigned short index) const;
    void V(unsigned short index) const;
    [[nodiscard]] bool isCreated() const;
private:
    SharedMemory nbProcess;
    int indexMutexShm;
};


#endif //BOMBER_STUDENT_SEMAPHORE_DYNAMIC_H
