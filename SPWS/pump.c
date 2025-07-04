#include "init.h"

extern config_t system_config;
extern uint8_t moisture;

int system_update();

void turn_pump_on()
{
    if(system_config.pump == PUMP_OFF)
    {
        system_config.pump = PUMP_ON; 
    }
}

void turn_pump_off()
{
    if(system_config.pump == PUMP_ON)
    {
        system_config.pump = PUMP_OFF; 
    }
}

void auto_pump()
{
    if (moisture < system_config.min_moisture_threshold)
    {
        printf("Moisture too low, starting watering...\n");
        turn_pump_on();

        for (int i = 0; i < system_config.pump_time; i++)
        {
            sleep(1);
            moisture += 3;
            printf("Moisture: %d%%\n", moisture);

            if (moisture >= system_config.max_moisture_threshold)
                break;
        }

        turn_pump_off();
        printf("Watering done. Pump off.\n");
    }
    else
    {
        printf("Humidity is ideal, no need to water.\n");
        turn_pump_off();
    }
}

