#ifndef BOMBER_STUDENT_UTILS_H
#define BOMBER_STUDENT_UTILS_H


#include <filesystem>

class Utils {
public:
    static std::filesystem::path getProgramPath();
    static std::string processName;
};


#endif //BOMBER_STUDENT_UTILS_H
