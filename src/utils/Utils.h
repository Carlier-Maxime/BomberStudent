#ifndef BOMBER_STUDENT_UTILS_H
#define BOMBER_STUDENT_UTILS_H


#include <filesystem>
#include <random>

#define SPLIT_POS(pos, x, y) \
    do { \
        y = static_cast<uint8_t>((pos) >> 8); \
        x = static_cast<uint8_t>((pos) & 0xFF); \
    } while(0)

#define MERGE_POS(x,y) ((static_cast<u_int16_t>(y)<<8) | static_cast<uint16_t>(x))

class Utils {
private:
    static std::mt19937 random_generator;
public:
    static std::filesystem::path getProgramPath();
    static std::string processName;
    static thread_local std::string threadName;
    static u_long getRandomNumber(u_long min, u_long max);
    static double getRandomNumber();
    static std::string trim(const std::string& str);
};


#endif //BOMBER_STUDENT_UTILS_H
