#include "init.h"

extern config_t system_config;
extern uint8_t moisture;

int system_update();

int turn_pump_on()
{
    if(system_config.pump == PUMP_OFF)
    {
        return system_config.pump = PUMP_ON; 
    }
    sleep(system_config.pump_time);
}

int turn_pump_off()
{
    if(system_config.pump == PUMP_ON)
    {
        return system_config.pump = PUMP_OFF; 
    }
}

void auto_pump()
{
    switch ((system_update()))
    {
        case SYS_NORMAL:
            printf("humidity is ideal, no need to water\n");
            turn_pump_off();
            break;
        
        case SYS_LOW_MOISTURE_ALERT:
        case SYS_WATERING:
            printf("watering\n");
            sleep(system_config.pump_time);
            while((sleep(system_config.pump_time)))
            {
                for(int i = 0; i < system_config.pump_time; i++)
                {
                    moisture += 3;
                    system_update();
                    auto_pump();
                    sleep(1);
                }
            }
            break;
        
        case SYS_ERROR:
            printf("Pump error\n");
            break;

        default:
            break;
    }
}
