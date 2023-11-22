#include <unistd.h>
#include "Utils.h"

std::string Utils::processName = "Unknown";

std::filesystem::path Utils::getProgramPath() {
    pid_t pid = getpid();
    std::string procPath = "/proc/" + std::to_string(pid) + "/exe";
    return std::filesystem::canonical(procPath.c_str()).string();
}