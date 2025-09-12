#include "Test_Service.h"

/*
generate 5 byte: 2 byte temp, 2 for humid, 1 for checksum
1 byte checksum = sum of 4 bytes, both temp and humid
*/

void Create_Data_Test(const char *filename, float temp, float humidity)
{
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("Can't open file");
        exit(1);
    }

    // Kiểm tra tràn số
    if (temp * 10 > UINT16_MAX || humidity * 10 > UINT16_MAX)
    {
        fprintf(stderr, "Temperature or humidity too large\n");
        close(fd);
        exit(1);
    }

    // Chuyển float sang dạng nhị phân 16 bit bằng cách nhân 10
    uint16_t temp_bin = (uint16_t)(temp * 10);
    uint16_t humid_bin = (uint16_t)(humidity * 10);

    uint8_t temp_high = (temp_bin >> 8) & 0xFF;
    uint8_t temp_low = temp_bin & 0xFF;
    uint8_t humid_high = (humid_bin >> 8) & 0xFF;
    uint8_t humid_low = humid_bin & 0xFF;
    uint8_t checksum = temp_high + temp_low + humid_high + humid_low;

    for (int i = temp_size - 1; i >= 0; i--)
    {
        uint8_t bit = (temp_bin >> i) & 1;
        if (dprintf(fd, "%d\n", bit) < 0)
        {
            perror("Failed to write temperature bit");
            close(fd);
            exit(1);
        }
    }

    for (int i = humi_size - 1; i >= 0; i--)
    {
        uint8_t bit = (humid_bin >> i) & 1;
        if (dprintf(fd, "%d\n", bit) < 0)
        {
            perror("Failed to write humidity bit");
            close(fd);
            exit(1);
        }
    }

    for (int i = checksum_length - 1; i >= 0; i--)
    {
        uint8_t bit = (checksum >> i) & 1;
        if (dprintf(fd, "%d\n", bit) < 0)
        {
            perror("Failed to write checksum bit");
            close(fd);
            exit(1);
        }
    }

    close(fd);
    printf("Data written to %s successfully.\n", filename);
}
