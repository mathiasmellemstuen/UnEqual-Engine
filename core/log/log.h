#include <string>

enum LogLevel {
    INFO = 1,
    SUCCESS = 2,
    WARNING = 3,
    ERROR = 4
};

void log(LogLevel logLevel, std::string text);
