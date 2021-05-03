#ifndef LOG
#define LOG

#include <string>
#include <iostream>
#include <ctime>
#include <glm/vec3.hpp>

#include "../sharedlib.h"

enum LogLevel {
    INFO = 1,
    SUCCESS = 2,
    WARNING = 3,
    ERROR = 4
};


void DLLEXPORT log(LogLevel logLevel, std::string text);
void DLLEXPORT log(LogLevel logLevel, glm::vec3 vec);

#endif