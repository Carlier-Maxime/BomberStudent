#ifndef BOMBER_STUDENT_SHARED_MEMORY_H
#define BOMBER_STUDENT_SHARED_MEMORY_H


class SharedMemory {
private:
    int IPCKeyID, shm_id;
    bool created;
    void *mem_ptr;

public:
    SharedMemory(int IPCKeyID, unsigned long size);
    ~SharedMemory();
    [[nodiscard]] bool isCreated() const;
    [[nodiscard]] void* getMemoryPointer() const;
};


#endif //BOMBER_STUDENT_SHARED_MEMORY_H
