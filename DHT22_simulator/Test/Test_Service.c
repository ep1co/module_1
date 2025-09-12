// include header files
#include "Test_Service.h"

// local constants


// local data type


// local variables


// local function prototype


// global function definition
/*
generate 5 byte: 2 byte temp, 2 for humid, 1 for checksum
1 byte checksum = sum of 4 bytes, both temp and humid
*/
void Create_Data_Test(const char *filename, float temp, float humidity)
{
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if(fd < 0)
    {
        perror("Can't open file");
        exit(1);
    }
    printf("File created successfully. Ready to write data.\n");
    // Product with 10 then convert to binary 16bit
    uint16_t temp_bin  = (uint16_t)(temp * 10);
    uint16_t humid_bin = (uint16_t)(humidity * 10);

    // Caculate checksum
    uint8_t temp_high  = (temp_bin >> 8) & 0xFF;
    uint8_t temp_low   = temp_bin & 0xFF;
    uint8_t humid_high = (humid_bin >> 8) & 0xFF;
    uint8_t humid_low  = humid_bin & 0xFF;

    uint8_t checksum = temp_high + temp_low + humid_high + humid_low;

    printf("Inserting start bits...\n");

    // 4. Ghi từng bit của temp (16 bit)
    for (int i = (temp_data_length - 1); i >= 0; i--) {
        uint8_t bit = (temp_bin >> i) & 1;
        dprintf(fd, "%d\n", bit);
    }

    // 5. Ghi từng bit của humid (16 bit)
    for (int i = (humid_data_length - 1); i >= 0; i--) {
        uint8_t bit = (humid_bin >> i) & 1;
        dprintf(fd, "%d\n", bit);
    }

    // 6. Ghi từng bit của checksum (8 bit)
    for (int i = (checksum_data_length - 1); i >= 0; i--) {
        uint8_t bit = (checksum >> i) & 1;
        dprintf(fd, "%d\n", bit);
    }
    printf("Data written successfully.\n");
    close(fd);
}

