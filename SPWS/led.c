#include "init.h"


//extern uint32_t led_state;
extern uint8_t moisture;

int system_update();

void display_led()
{
    switch (system_update())
    {
    case SYS_NORMAL:
        printf("GREEN\n");
        break;
    
    case SYS_WATERING:
        printf("BLUE\n");
        system_update();
        display_led();
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

