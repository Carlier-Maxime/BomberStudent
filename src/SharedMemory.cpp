#include "SharedMemory.h"
#include <sys/shm.h>
#include "Log.h"
#include "Utils.h"
#include "IPCKeyID.h"
#include "BomberStudentExceptions.h"

SharedMemory::SharedMemory(int IPCKeyID, size_t size) : IPCKeyID(IPCKeyID), shm_id(-1), mem_ptr(nullptr) {
    key_t key = ftok(Utils::getProgramPath().c_str(), IPCKeyID);
    if (key==-1) {
        throw IPCException("Key generation failed");
    }
    created=true;
    shm_id = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666);
    if (shm_id) created=false, shm_id=shmget(key,size,0600);
    if (shm_id == -1) {
        throw IPCException("Problem during creation of shared memory");
    }

    mem_ptr = shmat(shm_id, nullptr, 0);
    if (mem_ptr == reinterpret_cast<void*>(-1)) {
        throw IPCException("Problem during attachment of shared memory");
    }
}

SharedMemory::~SharedMemory() {
    if (shmdt(mem_ptr) == -1) {
        Log::warning("Problem during detachment of shared memory");
    }

    if (shmctl(shm_id, IPC_RMID, nullptr) == -1) {
        Log::warning("Problem during delete shared memory");
    }
}

void* SharedMemory::getMemoryPointer() const {
    return mem_ptr;
}

bool SharedMemory::isCreated() const {
    return created;
}
