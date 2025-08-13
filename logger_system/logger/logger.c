// include header files
#include "logger.h"

// global constants

// global data type
static logLevel current_level = LOG_DEBUG;
static FILE* log_file = NULL;

// global variables
const char* logLevel_string[] = 
{
    "EMERGENCY",
    "ALERT",
    "CRITICAL",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFO",
    "DEBUG"
};

// global function prototype

// global function definition
void logger_init(logLevel min_level, const char* filename) {
    current_level = min_level;
    if (filename) {
        log_file = fopen(filename, "a");
        if (!log_file) {
            perror("Failed to open log file");
        }
    }
}

void logger_log(logLevel level, const char* format, ...) {
    if (level > current_level) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

    va_list args;
    va_start(args, format);

    // Format log message
    char message[512];
    vsnprintf(message, sizeof(message), format, args);

    // Print to console
    if (level <= LOG_ERROR) {
        fprintf(stderr, "[%s] [%s] %s\n", timestamp, logLevel_string[level], message);
    } else {
        fprintf(stdout, "[%s] [%s] %s\n", timestamp, logLevel_string[level], message);
    }

    // Write to file if opened
    if (log_file) {
        fprintf(log_file, "[%s] [%s] %s\n", timestamp, logLevel_string[level], message);
        fflush(log_file);
    }

    va_end(args);
}

void logger_set_level(logLevel level) {
    current_level = level;
}

void logger_close() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}