#include "init.h"


int system_update();

void display_led()
{
    printf("Led color: "); 
    switch (system_update())
    {
    case SYS_NORMAL:
        printf("GREEN\n");
        break;
    
    case SYS_WATERING:
        printf("BLUE\n");
        break;
    
    case SYS_LOW_MOISTURE_ALERT:
        printf("YELLOW\n");
        break;
    
    case SYS_ERROR:
        printf("RED\n");
        break;

    default:
        break;
    }
}

