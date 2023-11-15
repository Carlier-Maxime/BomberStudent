#include "Mutex.h"
#include "SemaphoreDynamic.h"

Mutex::Mutex(int IPCKeyID, bool isDynamic) : isDynamic(isDynamic) {
    if (isDynamic) sem = new SemaphoreDynamic(IPCKeyID, 1, 1);
    else sem = new Semaphore(IPCKeyID, 1, 1);
}

void Mutex::P() {sem->P(0);}
void Mutex::V() {sem->V(0);}
bool Mutex::isCreated() {return sem->isCreated();}

Mutex::~Mutex() {
    if (isDynamic) delete (SemaphoreDynamic*) sem;
    else delete sem;
}
