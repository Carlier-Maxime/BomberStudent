#include <unistd.h>
#include "Utils.h"

std::mt19937 Utils::random_generator = std::mt19937(std::random_device{}());
std::string Utils::processName = "Unknown";
thread_local std::string Utils::threadName = "Main";

std::filesystem::path Utils::getProgramPath() {
    pid_t pid = getpid();
    std::string procPath = "/proc/" + std::to_string(pid) + "/exe";
    return std::filesystem::canonical(procPath);
}

u_long Utils::getRandomNumber(u_long min, u_long max) {
    std::uniform_int_distribution<u_long> range(min, max); // define the range
    return range(random_generator);
}