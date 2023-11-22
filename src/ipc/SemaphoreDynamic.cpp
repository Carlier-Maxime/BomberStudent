#include "SemaphoreDynamic.h"

SemaphoreDynamic::SemaphoreDynamic(int IPCKeyID, int nb, int value) : Semaphore(IPCKeyID, nb+(value==1 ? 0 : 1), value), nbProcess(IPCKeyID, sizeof(uint)) {
    indexMutexShm = value==1 ? nb-1 : nb;
    while (value<1) {
        Semaphore::V(indexMutexShm);
        value++;
    }
    while (value>1) {
        Semaphore::P(indexMutexShm);
        value--;
    }
    Semaphore::P(indexMutexShm);
    if (nbProcess.isCreated()) *static_cast<int *>(nbProcess.getMemoryPointer())=1;
    else (*static_cast<int *>(nbProcess.getMemoryPointer()))++;
    Semaphore::V(indexMutexShm);
}

SemaphoreDynamic::~SemaphoreDynamic() {
    Semaphore::P(indexMutexShm);
    (*static_cast<int *>(nbProcess.getMemoryPointer()))--;
    if ((*static_cast<int *>(nbProcess.getMemoryPointer()))==0) {
        nbProcess.del();
        del();
    }
    else Semaphore::V(indexMutexShm);
}