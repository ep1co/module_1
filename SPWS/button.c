/*
co 2 loai nut: nut chuyen mode va nut tuoi
mac dinh la mode AUTO
an nut 1 -> doi mode thanh MANUAL
an nut 2 -> tuoi nuoc
*/

#include <init.h>

extern uint8_t pump_mode;
extern uint8_t sys_mode;


void init_button()
{
    if(mode_button_pressed) 
    {
        if(sys_mode == MODE_AUTO)
        {
            sys_mode = MODE_MANUAL;
        }
        else sys_mode = MODE_AUTO;
    }
    if(pump_button_pressed)
    {
        if(pump_mode == PUMP_OFF)
        {
            pump_mode = PUMP_ON;
        }
        else pump_mode = PUMP_OFF;
    }
}
