#ifndef BOMBER_STUDENT_SEMAPHORE_H
#define BOMBER_STUDENT_SEMAPHORE_H

#include <string>
#include "SharedMemory.h"

class Semaphore {
public:
    Semaphore(int IPCKeyID, int nb, int value);
    void del();
    void P(unsigned short index) const;
    void V(unsigned short index) const;
    [[nodiscard]] bool isCreated() const;
    virtual ~Semaphore() = default;
protected:
    int nbSem;
private:
    int sem_id, IPCKeyID;
    bool created;
};


#endif //BOMBER_STUDENT_SEMAPHORE_H
