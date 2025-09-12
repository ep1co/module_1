#include "DHT22.h"
#include "Test_Service.h"



/*
2 read-bit functions gather bits into bytes and turn into decimal
return false if unable to open the file
*/


/*open exist file*/
FILE *fd_r = NULL;
bool DHT_Init(const char *filename)
{
    printf("Initializing...\n");
    fd_r = fopen(filename, "r");
    if (fd_r == NULL)
    {
        perror("Can't open file.");
        return false;
    }
    printf("Initialized successfully. Ready to read data.\n");
    return true;
}

static bool read_8bit(uint8_t *val)
{
    uint8_t value = 0;
    char line[16];
    for (int i = 7; i >= 0; i--)
    {
        if (fgets(line, sizeof(line), fd_r) == NULL)
        {
            fprintf(stderr, "File has fewer than expected lines for checksum\n");
            return false;
        }
        int bit;
        if (sscanf(line, "%d", &bit) != 1 || (bit != 0 && bit != 1))
        {
            fprintf(stderr, "Invalid bit value at line %d (checksum)\n", 8 - i);
            return false;
        }
        value |= (bit << i);
    }
    *val = value;
    return true;
}

/*read 2 byte, return false if invalid*/
bool DHT_Read_Temperature(float *temp)
{
    if (fd_r == NULL)
    {
        perror("File not initialized");
        return false;
    }

    if (fseek(fd_r, 0, SEEK_SET) != 0)
    {
        perror("Failed to seek file");
        return false;
    }

    uint16_t temp_bin = 0;
    char line[16];
    for (int i = temp_size - 1; i >= 0; i--)
    {
        if (fgets(line, sizeof(line), fd_r) == NULL)
        {
            fprintf(stderr, "File has fewer than 16 lines\n");
            return false;
        }
        int bit;
        if (sscanf(line, "%d", &bit) != 1 || (bit != 0 && bit != 1))
        {
            fprintf(stderr, "Invalid bit value at line %d\n", 16 - i);
            return false;
        }
        temp_bin |= (bit << i);
    }

    uint16_t humid_bin = 0;
    for (int i = humi_size - 1; i >= 0; i--)
    {
        if (fgets(line, sizeof(line), fd_r) == NULL)
        {
            fprintf(stderr, "File has fewer than 32 lines\n");
            return false;
        }
        int bit;
        if (sscanf(line, "%d", &bit) != 1 || (bit != 0 && bit != 1))
        {
            fprintf(stderr, "Invalid bit value at line %d (humidity)\n", 32 - i);
            return false;
        }
        humid_bin |= (bit << i);
    }

    uint8_t checksum;
    if (!read_8bit(&checksum))
    {
        return false;
    }

    uint8_t temp_high = (temp_bin >> 8) & 0xFF;
    uint8_t temp_low = temp_bin & 0xFF;
    uint8_t humid_high = (humid_bin >> 8) & 0xFF;
    uint8_t humid_low = humid_bin & 0xFF;
    uint8_t calc_checksum = temp_high + temp_low + humid_high + humid_low;

    if (calc_checksum != checksum)
    {
        fprintf(stderr, "Checksum mismatch: calculated %d, read %d\n", calc_checksum, checksum);
        return false;
    }

    *temp = (float)temp_bin / 10.0f;
    return true;
}

/*read 2 byte, return false if invalid*/
bool DHT_Read_Humidity(float *humidity)
{
    if (fd_r == NULL)
    {
        perror("File not initialized");
        return false;
    }

    if (fseek(fd_r, 0, SEEK_SET) != 0)
    {
        perror("Failed to seek file");
        return false;
    }

    char line[16];
    for (int i = 0; i < temp_size; i++)
    {
        if (fgets(line, sizeof(line), fd_r) == NULL)
        {
            fprintf(stderr, "File has fewer than 16 lines\n");
            return false;
        }
    }

    uint16_t humid_bin = 0;
    for (int i = humi_size - 1; i >= 0; i--)
    {
        if (fgets(line, sizeof(line), fd_r) == NULL)
        {
            fprintf(stderr, "File has fewer than 32 lines\n");
            return false;
        }
        int bit;
        if (sscanf(line, "%d", &bit) != 1 || (bit != 0 && bit != 1))
        {
            fprintf(stderr, "Invalid bit value at line %d (humidity)\n", 32 - i);
            return false;
        }
        humid_bin |= (bit << i);
    }

    uint8_t checksum;
    if (!read_8bit(&checksum))
    {
        return false;
    }

    if (fseek(fd_r, 0, SEEK_SET) != 0)
    {
        perror("Failed to seek file");
        return false;
    }
    uint16_t temp_bin = 0;
    for (int i = temp_size - 1; i >= 0; i--)
    {
        if (fgets(line, sizeof(line), fd_r) == NULL)
        {
            fprintf(stderr, "File has fewer than 16 lines\n");
            return false;
        }
        int bit;
        if (sscanf(line, "%d", &bit) != 1 || (bit != 0 && bit != 1))
        {
            fprintf(stderr, "Invalid bit value at line %d\n", 16 - i);
            return false;
        }
        temp_bin |= (bit << i);
    }

    uint8_t temp_high = (temp_bin >> 8) & 0xFF;
    uint8_t temp_low = temp_bin & 0xFF;
    uint8_t humid_high = (humid_bin >> 8) & 0xFF;
    uint8_t humid_low = humid_bin & 0xFF;
    uint8_t calc_checksum = temp_high + temp_low + humid_high + humid_low;

    if (calc_checksum != checksum)
    {
        fprintf(stderr, "Checksum mismatch: calculated %d, read %d\n", calc_checksum, checksum);
        return false;
    }

    *humidity = (float)humid_bin / 10.0f;
    return true;
}
