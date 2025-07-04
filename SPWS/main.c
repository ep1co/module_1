#include "init.h"

void show_temperature();
void show_moisture();
void init_button();
void led_update();

int main()
{
    printf("Starting...\n");
    while (1)
    {
        printf("---------------------\n");
        //update_temperature();
        show_temperature();

        //update_humidity();
        show_moisture();
        sleep(system_config.sys_delay);
    }

    printf("Shutting down.\n");

}

