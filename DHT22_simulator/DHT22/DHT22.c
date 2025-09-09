// include header files
#include "DHT22.h"
//#include "Test_Service.h"

// local constants


//local data type


// local variables


// local function prototype


// global function definition
/*
2 ham read gop bit thanh cac byte va quy doi sang decimal
return false if cannot open the file
change 2 byte in binary to decimal -> readable results

*/

/*
mo file da co san
*/
static FILE *fd_r = NULL;
bool DHT_Init(const char *filename)
{
    fd_r = fopen(filename, "r");
    if (fd_r == NULL)
    {
        perror("Can't open file.");
        return false;
    }
    printf("File opened successfully. Ready to read data.\n");
    return true;
}

static bool read_16bit(uint16_t *val)
{
    uint16_t value = 0;
    for (int i = 0; i < 16; i++) {
        int bit;
        if (fscanf(fd_r, "%d", &bit) != 1) {
            return false;
        }
        value = (value << 1) | (bit & 1);
    }
    *val = value;
    return true;
}

/*
put bits in 3rd and 4th byte, then converse the number as float, remember to devide by 10
read 2 byte, return false if invalid*/

bool DHT_Read_Temperature(float *temp)
{
    uint16_t raw;
    if (!read_16bit(&raw)) return false;
    *temp = (float)raw / 10.0f;
    return true;
}

/*read 2 byte, return false if invalid*/
bool DHT_Read_Humidity(float *humidity)
{
    uint16_t raw;
    if (!read_16bit(&raw)) return false;
    *humidity = (float)raw / 10.0f;
    return true;
}
