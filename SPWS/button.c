#include "init.h"

void init_button()
{
    if (mode_button_pressed) 
    {
        if (system_config.sys_mode == MODE_AUTO)
        {
            turn_pump_off();
            system_config.sys_mode = MODE_MANUAL;
            printf("Manual mode enabled.\n");
        }
        else
        {
            system_config.sys_mode = MODE_AUTO;
            printf("Auto mode enabled.\n");
            printf("Press any key to water.\n");
        }
    }

    if (pump_button_pressed)
    {
        if (system_config.pump == PUMP_OFF)
        {
            system_config.pump = PUMP_ON;
            printf("Watering...\n");
            sleep(10);
        }
        else 
        {
            system_config.pump = PUMP_OFF;
            printf("Pump turned off.\n");
        }
    }
}
