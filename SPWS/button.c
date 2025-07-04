/*
co 2 loai nut: nut chuyen mode va nut tuoi
mac dinh la mode AUTO
an nut 1 -> doi mode thanh MANUAL
an nut 2 -> tuoi nuoc
*/

#include "init.h"

void auto_pump();
void turn_pump_off();


void init_mode_button()
{
    if (mode_button_pressed) 
    {
        if (system_config.sys_mode == MODE_AUTO)
        {
            turn_pump_off();
            system_config.sys_mode = MODE_MANUAL;
            printf("Manual mode enabled.\n");
            printf("Press 'W' to water.\n");
            press_button();
        }
        else
        {
            system_config.sys_mode = MODE_AUTO;
            printf("Auto mode enabled.\n");
            auto_pump();
        }
    }
}

void init_pump_button()
{
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
    
void press_button()
{
    char ch = getchar();
    while (ch != '\n')
    {
        if (ch == 'w') system_config.pump = PUMP_ON;
        else if (ch == 'p') init_mode_button();
        else if (ch == 'm') init_pump_button();
    }
}

    
