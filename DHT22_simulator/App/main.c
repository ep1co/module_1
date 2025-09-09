// include header files
//#include "DHT22.h"
#include "Test_Service.h"




// local constants
#define name_size               (30)


//local data type



// local variables



// global function prototype
void Create_Data_Test();
bool DHT_Init();
bool DHT_Read_Temperature();
bool DHT_Read_Humidity();


// global function definition
int main(void)
{
    float temp, humi;
    printf("Insert desired temperature and humid, separated by space: ");
    scanf("%f %f", &temp, &humi);
    // printf("Type file name to save data: ");
    // char fileName[name_size];
    // scanf("%29s", fileName);
    printf("flag...\n");
    Create_Data_Test("sdf.txt", temp, humi);
    Create_Data_Test("data.txt", 36, 63.4);
    //printf("Data written to %29s successfully\n", fileName);
    DHT_Init("sdf.txt");
    if(DHT_Read_Temperature(temp))
    {
        printf("Temperature: %.1f\n", temp);
    }
    if(DHT_Read_Humidity(humi))
    {
        printf("Humidity: %.1f\n", humi);
    }

    return 0;
}


