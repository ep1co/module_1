#include <init.h>

extern uint32_t led_state;
extern uint16_t humidity;

void led_update()
{
    if(turn_pump_off() && humidity >= MIN_HUMID)
    {
        led_state = LED_NORMAL;
    }
    else if(turn_pump_on())
    {
        led_state = LED_WATERING;
    }
    else if(humidity < MIN_HUMID)
    {
        led_state = LED_LOW_MOISTURE_ALERT;
    }
    else
    {
        led_state = LED_ERROR;
    }

    switch (led_state)
    {
    case LED_NORMAL:
        printf("GREEN\n");
        break;
    
    case LED_WATERING:
        printf("BLUE\n");
        break;
    
    case LED_LOW_MOISTURE_ALERT:
        printf("YELLOW\n");
        break;
    
    case LED_ERROR:
        printf("RED\n");
        break;

    default:
        break;
    }
}

