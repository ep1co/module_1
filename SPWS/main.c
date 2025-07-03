/*
cac trang thai:
1. system mode
2. bom nuoc
3. led
*/

/*
thu tu show len man hinh:

---------------------
mode: AUTO
temperature: 27 *C
humidity: 70 %
pump: ON 
led: BLUE
---------------------

*/

#include <init.h>

void update_temperature();
void show_temperature();
void update_humidity();
void show_humidity();

typedef struct
{
    MODE_MANUAL,
    PUMP_OFF 
} default_state;

int main()
{
    printf("Starting...\n");
    for(int index = 0; index < 10; index++)
    {
        printf("---------------------\n");
        update_temperature();
        show_temperature();

        update_humidity();
        show_humidity();

        delay_ms(1000);
        printf("---------------------\n");
    }
    printf("Shutting down.\n");
}

