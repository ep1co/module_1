#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>


// include header files


// Constant
typedef enum 
{
    LOG_EMERGENCY,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG,
} logLevel;
#define log_message(level, format, ...) logger_log(level, "[%s:%d] " format, __FILE__, __LINE__, ##__VA_ARGS__)

//  Data type


// Function prototype
void logger_init(logLevel min_level, const char* filename);
void logger_log(logLevel level, const char* format, ...);
void logger_set_level(logLevel level);
void logger_close();


#endif 
