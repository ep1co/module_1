#include "init.h"

extern uint8_t temperature;
extern uint8_t moisture;

void update_temperature()
{
    temperature = rand() % (30 - 25 + 1) + 25;
}

void update_moisture()
{
    moisture = rand() % (90 - 20 + 1) + 20;
}
