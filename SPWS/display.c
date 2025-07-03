//in ket qua len terminal
#include <init.h>

extern int temperature;

void show_temperature()
{    
    printf("Temp: %d\n", temperature);
}

void show_humidity()
{
    extern int humidity;
    if(humidity >= MIN_HUMID)
    {
        printf("humidity is ideal, no need to water\n");
        turn_pump_off();

    }
    else
    {
        printf("watering...\n");
        turn_pump_on();
    }
    printf("Humid: %d", humidity);
}