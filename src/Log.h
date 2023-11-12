#ifndef BOMBER_STUDENT_LOG_H
#define BOMBER_STUDENT_LOG_H

#include <fstream>
#include <string>
#include <sstream>
#include "Mutex.h"

class Log {
public:
    static void open();
    static void close();
    static void info(const std::string& msg);
    static void warning(const std::string& msg);
    static void error(const std::string& msg);

private:
    enum class LogType {
        Info,
        Warning,
        Error
    };
    static std::ofstream log_file;
    static std::string getTimestamp();
    static void write(LogType logType, const std::string& msg);
    static Mutex mutex;
};

#endif //BOMBER_STUDENT_LOG_H
