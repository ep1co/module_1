#include "init.h"

uint8_t mode_button_pressed = 0;
uint8_t pump_button_pressed = 0;
uint8_t temperature;
uint8_t moisture;
config_t system_config;
system_mode sys_mode;

void init_default_config()
{
    system_config.max_moisture_threshold = 80;
    system_config.min_moisture_threshold = 50;
    system_config.pump_time = 10;
    system_config.sys_delay = 5;
    system_config.sys_mode = MODE_AUTO;
    system_config.pump = PUMP_OFF;
}

