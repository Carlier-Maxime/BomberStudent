#include <unistd.h>
#include "Utils.h"

std::string Utils::processName = "Unknown";
thread_local std::string Utils::threadName = "Main";

std::filesystem::path Utils::getProgramPath() {
    pid_t pid = getpid();
    std::string procPath = "/proc/" + std::to_string(pid) + "/exe";
    return std::filesystem::canonical(procPath);
}