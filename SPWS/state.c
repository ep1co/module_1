#include "init.h"

int turn_pump_off();
int turn_pump_on();

int system_update() //for a whole system
{
    system_state systemState; 
    if((turn_pump_off()) && moisture >= system_config.min_moisture_threshold)
    {
        systemState = SYS_NORMAL;
    }
    else if((turn_pump_on()))
    {
        systemState = SYS_WATERING;
    }
    else if(moisture < system_config.min_moisture_threshold)
    {
        systemState = SYS_LOW_MOISTURE_ALERT;
    }
    else
    {
        systemState = SYS_ERROR;
    }
    return systemState;
}

