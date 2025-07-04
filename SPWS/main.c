#include "init.h"

void show_mode();
void update_temperature();
void update_moisture();
void show_temperature();
void show_moisture();
void led_update();
void press_button();
void display_led();
void init_mode_button();
void init_pump_button();
void init_default_config();
int system_update();
void show_water_state();
void auto_pump();

extern config_t system_config;

int main(void)
{
    init_default_config();
    printf("Starting...\n");
    while (1)
    {
        printf("---------------------\n");
        show_mode();
        update_temperature();
        show_temperature();
        update_moisture();
        show_moisture();
        system_update();
        display_led();
        show_water_state();
        if (system_config.sys_mode == MODE_AUTO) 
        {
            auto_pump();        
        }
        press_button();
        sleep(system_config.sys_delay);
    }

    return 0;
}

