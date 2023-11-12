#include "SharedMemory.h"
#include <sys/shm.h>
#include "Log.h"
#include "Utils.h"
#include "IPCKeyID.h"

SharedMemory::SharedMemory(int IPCKeyID, size_t size) : IPCKeyID(IPCKeyID), shm_id(-1), mem_ptr(nullptr) {
    key_t key = ftok(Utils::getProgramPath().c_str(), IPCKeyID);
    if (key==-1) {
        if (IPCKeyID != IPCKeyID::LOGGER) Log::system_error("Key generation failed");
        throw std::exception();
    }
    created=true;
    shm_id = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666);
    if (shm_id) created=false, shm_id=shmget(key,size,0600);
    if (shm_id == -1) {
        if (IPCKeyID != IPCKeyID::LOGGER) Log::system_error("Error during creation of shared memory");
        throw std::exception();
    }

    mem_ptr = shmat(shm_id, nullptr, 0);
    if (mem_ptr == reinterpret_cast<void*>(-1)) {
        if (IPCKeyID != IPCKeyID::LOGGER) Log::system_error("Error during attachment of shared memory");
        throw std::exception();
    }
}

SharedMemory::~SharedMemory() {
    if (shmdt(mem_ptr) == -1) {
        if (IPCKeyID != IPCKeyID::LOGGER) Log::system_error("Error during detachment of shared memory");
    }

    if (shmctl(shm_id, IPC_RMID, nullptr) == -1) {
        if (IPCKeyID != IPCKeyID::LOGGER) Log::system_error("Error during delete shared memory");
    }
}

void* SharedMemory::getMemoryPointer() const {
    return mem_ptr;
}

bool SharedMemory::isCreated() const {
    return created;
}
