#include "Semaphore.h"
#include "../utils/Log.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include "../utils/Utils.h"
#include "../utils/BomberStudentExceptions.h"

#define ERR (-1)

Semaphore::Semaphore(int IPCKeyID, int nb, int value) : nbSem(nb), IPCKeyID(IPCKeyID) {
    key_t key = ftok((Utils::getProgramPath().parent_path() / "bomberStudentServer").c_str(), IPCKeyID);
    if (key==ERR) {
        throw IPCException("Key generation failed");
    }
    created=true;
    sem_id=semget(key,nb,IPC_CREAT|IPC_EXCL|0600);
    if(sem_id==ERR) created=false, sem_id=semget(key,nb,0600);
    if(sem_id==ERR) {
        throw IPCException("Problem during initialization of semaphore");
    }
    if (created) for(int i=0;i<nb;i++) if(semctl(sem_id,i,SETVAL,value)==ERR) {
        throw IPCException("Problem during initialization of semaphore");
    }
}

void Semaphore::del() {
    if (semctl(sem_id,1,IPC_RMID)==ERR) Log::warning("Problem during the deletion of semaphore");
}

void Semaphore::P(unsigned short index) const {
    struct sembuf P_op={index,-1,0};
    if(semop(sem_id,&P_op,1)==ERR) {
        throw IPCException("Problem during P operation on the semaphore");
    }
}

void Semaphore::V(unsigned short index) const {
    struct sembuf V_op={index,1,0};
    if(semop(sem_id,&V_op,1)==ERR) {
        throw IPCException("Problem during V operation on the semaphore");
    }
}

bool Semaphore::isCreated() const {
    return created;
}
