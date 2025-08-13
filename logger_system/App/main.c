// include header files
#include "logger.h"

// glocal constants

// glocal data type

// glocal variables

// glocal function prototype

// global function definition
int main() {
    logger_init(LOG_INFO, "app.log");
    log_message(LOG_INFO, "This is an info message.");
    log_message(LOG_ERROR, "An error occurred: %s", "connection failed");
    log_message(LOG_DEBUG, "This debug message will not be shown.");

    logger_close();
    return 0;
}


