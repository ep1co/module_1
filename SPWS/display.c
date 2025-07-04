#include "init.h"


int system_update();

void show_temperature()
{    
    printf("Temp: %d *C\n", temperature);
}


void show_moisture()
{
    printf("Moisture: %d %%", moisture);
}


void show_water_state()
{
    switch (system_update())
    {
        case SYS_NORMAL:
            break;
    
        case SYS_WATERING:
            printf("Watering...\n");
            break;
        
        case SYS_LOW_MOISTURE_ALERT:
            printf("Low moisture\n");
            break;
        
        case SYS_ERROR:
            printf("Error\n");
            break;

        default:
            break;
    }
}

void show_mode()
{
    if(sys_mode == MODE_AUTO) printf("Mode: Auto");
    else printf("Mode: Manual");
}
