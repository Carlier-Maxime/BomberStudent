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
    return std::uniform_int_distribution<u_long>(min, max)(random_generator);
}

double Utils::getRandomNumber() {
    return std::uniform_real_distribution<>(0,1)(random_generator);
}

std::string Utils::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == std::string::npos || last == std::string::npos) return "";
    return str.substr(first, last-first+1);
}