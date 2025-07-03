#include <stdint.h>
#include <stdio.h>


#define MAX_HUMID 80
#define MIN_HUMID 60
#define MODE_MANUAL 0
#define MODE_AUTO 1
#define PUMP_OFF 0
#define PUMP_ON 1
#define LED_NORMAL 7
#define LED_WATERING 8
#define LED_LOW_MOISTURE_ALERT 9
#define LED_ERROR 10


uint8_t sys_mode;
uint8_t mode_button_pressed = 0;
uint8_t pump_button_pressed = 0; 
uint16_t temperature;
uint16_t humidity;
uint32_t led_state;
