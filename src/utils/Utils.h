#ifndef BOMBER_STUDENT_UTILS_H
#define BOMBER_STUDENT_UTILS_H


#include <filesystem>
#include <random>

class Utils {
private:
    static std::mt19937 random_generator;
public:
    static std::filesystem::path getProgramPath();
    static std::string processName;
    static thread_local std::string threadName;
    static u_long getRandomNumber(u_long min, u_long max);
};


#endif //BOMBER_STUDENT_UTILS_H
