#include "Mutex.h"

Mutex::Mutex(int IPCKeyID) : Semaphore(IPCKeyID, 1, 1) {}

void Mutex::P() {Semaphore::P(0);}
void Mutex::V() {Semaphore::V(0);}

Mutex::~Mutex() = default;
