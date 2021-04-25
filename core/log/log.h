#ifndef LOG
#define LOG

#include <string>
#include <iostream>
#include <ctime>

#include "../sharedlib.h"

enum LogLevel {
    INFO = 1,
    SUCCESS = 2,
    WARNING = 3,
    ERROR = 4
};


void DLLEXPORT log(LogLevel logLevel, std::string text);

#endif