#include <cstring>
#include "BomberStudentExceptions.h"

SocketException::SocketException(const std::string& msg) : SystemException(msg) {}

SystemException::SystemException(const std::string &msg) : runtime_error(msg+" : "+std::string(strerror(errno))) {}

IPCException::IPCException(const std::string &msg) : SystemException(msg) {}
