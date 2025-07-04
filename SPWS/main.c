#include "init.h"

void show_mode();
void show_temperature();
void show_moisture();
void led_update();
void press_button();
void display_led();

void main(void)
{
    printf("Starting...\n");
    while (1)
    {
        printf("---------------------\n");
        show_mode();
        show_temperature();
        show_moisture();
        display_led();
        press_button();
        sleep(system_config.sys_delay);
    }

    printf("Shutting down.\n");
}

