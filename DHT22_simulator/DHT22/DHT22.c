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

/*
put bits in 3rd and 4th byte, then converse the number as float, remember to devide by 10
read 2 byte, return false if invalid*/

bool DHT_Read_Temperature(float *temp)
{
    // Mở file để đọc
    FILE *f = fopen("data.txt", "r");
    if (!f) {
        perror("Cannot open file");
        return false;
    }

    // Đọc 16 bit đầu tiên
    uint16_t temp_bin = 0;
    char line[16]; // Buffer để đọc từng dòng (giả sử mỗi dòng chứa số 0 hoặc 1)
    for (int i = 15; i >= 0; i--) {
        if (fgets(line, sizeof(line), f) == NULL) {
            fprintf(stderr, "File has fewer than 16 lines\n");
            fclose(f);
            return false;
        }

        // Chuyển đổi dòng thành số (0 hoặc 1)
        int bit;
        if (sscanf(line, "%d", &bit) != 1 || (bit != 0 && bit != 1)) {
            fprintf(stderr, "Invalid bit value at line %d\n", 16 - i);
            fclose(f);
            return false;
        }

        // Dịch trái và thêm bit vào temp_bin
        temp_bin |= (bit << i);
    }

    // Quy đổi sang float
    *temp = (float)temp_bin / 10.0f;

    // Đóng file
    fclose(f);
    return true;
}

/*read 2 byte, return false if invalid*/
bool DHT_Read_Humidity(float *humidity)
{
    // Mở file để đọc
    FILE *f = fopen("data.txt", "r");
    if (!f) {
        perror("Cannot open file");
        return false;
    }

    char line[16];

    // Bỏ qua 16 dòng đầu (temperature)
    for (int i = 0; i < 16; i++) {
        if (fgets(line, sizeof(line), f) == NULL) {
            fprintf(stderr, "File has fewer than 32 lines (need at least 16 for humidity)\n");
            fclose(f);
            return false;
        }
    }

    // Đọc 16 bit tiếp theo (humidity)
    uint16_t humid_bin = 0;
    for (int i = 15; i >= 0; i--) {
        if (fgets(line, sizeof(line), f) == NULL) {
            fprintf(stderr, "File has fewer than 32 lines\n");
            fclose(f);
            return false;
        }

        int bit;
        if (sscanf(line, "%d", &bit) != 1 || (bit != 0 && bit != 1)) {
            fprintf(stderr, "Invalid bit value at line %d (humidity)\n", 32 - i);
            fclose(f);
            return false;
        }

        humid_bin |= (bit << i);
    }

    // Quy đổi sang float
    *humidity = (float)humid_bin / 10.0f;

    fclose(f);
    return true;
}
