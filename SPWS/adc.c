#include <stdio.h>
#include <init.h>
#include <stdint.h>

void update_temperature()
{
    temperature = rand() % (30 - 25 + 1) + 25;
}

void update_humidity()
{
    humidity = rand() % (90 - 20 + 1) + 20;
}
