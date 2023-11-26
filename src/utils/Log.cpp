#include <ctime>
#include "Log.h"
#include "../ipc/IPCKeyID.h"
#include "Utils.h"
#include "Config.h"

std::ofstream Log::log_file;
Mutex Log::mutex = Mutex(IPCKeyID::LOGGER, true);

void Log::open() {
    log_file.open(Config::getLogFilePath(), std::ios::out | (mutex.isCreated() ? std::ios::trunc : std::ios ::app));
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

std::string Log::getTimestamp() {
    char filename[32];
    std::time_t now = std::time(nullptr);
    struct std::tm* timeInfo = std::localtime(&now);
    std::strftime(filename, sizeof(filename), "[%Y-%m-%d %H:%M:%S]", timeInfo);
    return filename;
}

void Log::write(Log::LogType logType, const std::string& msg) {
    mutex.P();
    log_file.seekp(0, std::ios::end);
    log_file << Log::getTimestamp() << " [" << Utils::processName << ":" << Utils::threadName << "/";
    switch (logType) {
        case LogType::Info:
            log_file << "INFO";
            break;
        case LogType::Warning:
            log_file << "WARNING";
            break;
        case LogType::Error:
            log_file << "ERROR";
            break;
    }
    log_file << "]: ";
    log_file << msg << std::endl;
    mutex.V();
}
