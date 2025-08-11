// include header files
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

// global constants

// global data type

// global variables

// global function prototype

// global function definition
void print_file_type(mode_t mode) {
    printf("File Type: ");
    if (S_ISREG(mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic Link\n");
    } else {
        printf("Other\n");
    }
}

int print_fileStat(int argc, char *argv[])
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
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last Modified: %s\n", timebuf);
    return 0;
}
