#include <ctime>
#include <iostream>
#include <cstring>
#include "Log.h"

std::ofstream Log::log_file;

void Log::open() {
    log_file.open("log.txt", std::ios::out | std::ios::trunc);
}

void Log::close() {
    log_file.close();
}

void Log::info(const std::string& msg) {
    Log::write(LogType::Info, msg);
}

void Log::warning(const std::string& msg) {
    Log::write(LogType::Warning, msg);
}

void Log::error(const std::string& msg) {
    Log::write(LogType::Error, msg);
}

void Log::system_error(const std::string& msg) {
    std::string final_msg = msg+" : ";
    Log::write(LogType::Error, final_msg.append(std::string(strerror(errno))));
}

std::string Log::getTimestamp() {
    char filename[32];
    std::time_t now = std::time(nullptr);
    struct std::tm* timeInfo = std::localtime(&now);
    std::strftime(filename, sizeof(filename), "[%Y-%m-%d %H:%M:%S]", timeInfo);
    return filename;
}

void Log::write(Log::LogType logType, const std::string& msg) {
    log_file << Log::getTimestamp();
    switch (logType) {
        case LogType::Info:
            log_file << "[INFO] ";
            break;
        case LogType::Warning:
            log_file << "[WARNING] ";
            break;
        case LogType::Error:
            log_file << "[ERROR] ";
            break;
    }
    log_file << msg << std::endl;
}
