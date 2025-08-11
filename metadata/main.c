// include header files
#include "filestat.h"

// local constants

// local data type

// local variables

// local function prototype
int print_file_type();
void Function_From_SWC2();

// global function definition
int main(int argc, char *argv[])
{
struct stat fileStat;

    // 1.2 Kiểm tra số lượng tham số
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    char *filePath = argv[1];

    // 1.3 Dùng lstat() để lấy thông tin file
    if (lstat(filePath, &fileStat) == -1) {
        perror("lstat");
        return 1;
    }

    // 1.4 In thông tin
    printf("File Path: %s\n", filePath);

    print_file_type(fileStat.st_mode);

    printf("Size: %lld bytes\n", (long long)fileStat.st_size);

    // Lấy thời gian chỉnh sửa cuối
    char timebuf[100];
    struct tm *timeinfo = localtime(&fileStat.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%%Y-%%m-%%d %%H:%%M:%%S", timeinfo);
    printf("Last Modified: %s\n", timebuf);

    Function_From_SWC2();

    return 0;
}
