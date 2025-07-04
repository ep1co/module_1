#ifndef INIT_H
#define INIT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum
{
    MODE_AUTO   = 1,
    MODE_MANUAL = 0 
} system_mode;

typedef enum
{
    PUMP_ON     = 1,
    PUMP_OFF    = 0
} pump_state;

typedef enum
{
    SYS_NORMAL                  = 7,
    SYS_WATERING                = 8,
    SYS_LOW_MOISTURE_ALERT      = 9,
    SYS_ERROR                   = 10
} system_state;

typedef struct
{
    uint8_t max_moisture_threshold;
    uint8_t min_moisture_threshold;
    uint8_t pump_time;
    uint8_t sys_delay;
    system_mode sys_mode;
    pump_state pump;
} config_t;

#endif
