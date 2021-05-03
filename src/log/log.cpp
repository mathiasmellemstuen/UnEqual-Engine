#include "log.h"
#include <string>
#include <iostream>
#include <ctime>


void log(LogLevel logLevel, std::string text) {
    std::string logLevelString = ""; 
    
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    
    switch (logLevel) {
       case INFO: 
            logLevelString = "\e[1;36m[INFO]";
            break; 
        case SUCCESS:
            logLevelString = "\e[1;32m[SUCCESS]";
            break; 
        case WARNING: 
            logLevelString = "\e[1;33m[WARNING]";
            break; 
        case ERROR: 
            logLevelString = "\e[1;34m[ERROR]";
    }
    std::cout << logLevelString << "[" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec  << "]" << "\e[0m" << " " << text << std::endl;

}
void log(LogLevel logLevel, glm::vec3 vec) {
    log(logLevel, "x: " + std::to_string(vec.x) + " y: " + std::to_string(vec.y) + " z: " + std::to_string(vec.z));
}