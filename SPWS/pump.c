#include <stdio.h>
#include <init.h>

extern int temperature;
extern int humidity;

void turn_pump_on()
{

}

void turn_pump_off()
{
    
}

struct state
{

};

void pump_state()
{
    if (humidity >= MAX_HUMID)
    {
        turn_pump_off();
    }
    else turn_pump_on();
}
