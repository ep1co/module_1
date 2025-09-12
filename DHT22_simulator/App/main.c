#include "Test_Service.h"
#include "DHT22.h"


void Create_Data_Test();
bool DHT_Init();
bool DHT_Read_Temperature();
bool DHT_Read_Humidity();


int main(void)
{
    float temp, humi;
    printf("Insert desired temperature and humid, separated by space: ");
    if (scanf("%f %f", &temp, &humi) != 2)
    {
        printf("Invalid input\n");
        return 1;
    }
    printf("Type file name to save data: ");
    char fileName[name_size];
    scanf("%29s", fileName);
    Create_Data_Test(fileName, temp, humi);
    if (DHT_Init(fileName))
    {
        if (DHT_Read_Temperature(&temp))
        {
            printf("Temperature: %.1f\n", temp);
        }
        else
        {
            printf("Failed to read temperature\n");
        }
        if (DHT_Read_Humidity(&humi))
        {
            printf("Humidity: %.1f\n", humi);
        }
        else
        {
            printf("Failed to read humidity\n");
        }
        if (fd_r != NULL)
        {
            fclose(fd_r);
            fd_r = NULL;
        }
    }
    return 0;
}



