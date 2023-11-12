#include "Semaphore.h"
#include "Log.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include "Utils.h"
#include "IPCKeyID.h"

#define ERR (-1)

Semaphore::Semaphore(int IPCKeyID, int nb, int value) : IPCKeyID(IPCKeyID), nbProcess(IPCKeyID, sizeof(uint)) {
    key_t key = ftok(Utils::getProgramPath().c_str(), IPCKeyID);
    if (key==ERR) {
        if (IPCKeyID != IPCKeyID::LOGGER) Log::system_error("Key generation failed");
        throw std::exception();
    }
    created=true;
    sem_id=semget(key,nb,IPC_CREAT|IPC_EXCL|0600);
    if(sem_id==ERR) created=false, sem_id=semget(key,nb,0600);
    if(sem_id==ERR) {
        Log::system_error("Problem during initialization of semaphore");
        throw std::exception();
    }
    if (created) for(int i=0;i<nb;i++) if(semctl(sem_id,i,SETVAL,value)==ERR) {
        if (IPCKeyID != IPCKeyID::LOGGER) Log::system_error("Problem during initialization of semaphore");
        throw std::exception();
    }
    if (nbProcess.isCreated()) *static_cast<int *>(nbProcess.getMemoryPointer())=1;
    else (*static_cast<int *>(nbProcess.getMemoryPointer()))++;
}

Semaphore::~Semaphore() {
    (*static_cast<int *>(nbProcess.getMemoryPointer()))--;
    if (*static_cast<int *>(nbProcess.getMemoryPointer())>0) return;
    if ((semctl(sem_id,1,IPC_RMID)==ERR)&&(errno!=EPERM)) {
        if (IPCKeyID != IPCKeyID::LOGGER) Log::system_error("Problem during the deletion of semaphore");
    }
}

void Semaphore::P(unsigned short index) const {
    struct sembuf P_op={index,-1,0};
    if(semop(sem_id,&P_op,1)==ERR) {
        if (IPCKeyID != IPCKeyID::LOGGER) Log::system_error("Problem during P operation on the semaphore");
        throw std::exception();
    }
}

void Semaphore::V(unsigned short index) const {
    struct sembuf V_op={index,1,0};
    if(semop(sem_id,&V_op,1)==ERR) {
        if (IPCKeyID != IPCKeyID::LOGGER) Log::system_error("Problem during V operation on the semaphore");
        throw std::exception();
    }
}

bool Semaphore::isCreated() const {
    return created;
}
