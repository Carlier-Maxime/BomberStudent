#ifndef BOMBER_STUDENT_BOMBER_STUDENT_EXCEPTIONS_H
#define BOMBER_STUDENT_BOMBER_STUDENT_EXCEPTIONS_H

#include <stdexcept>

class SystemException : public std::runtime_error {
public:
    explicit SystemException(const std::string& msg);
};

class SocketException : public SystemException {
public:
    explicit SocketException(const std::string& msg);
};

class IPCException : public SystemException {
public:
    explicit IPCException(const std::string& msg);
};

#endif //BOMBER_STUDENT_BOMBER_STUDENT_EXCEPTIONS_H
