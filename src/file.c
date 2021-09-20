#include <file.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

char FILEPATH[255];

// Loads a ROM into memory at 0x200
void load_ROM(char* arg) {
    strcat(FILEPATH, "ROM/");
    strcat(FILEPATH, arg);

    FILE* fp;
    fp = fopen(FILEPATH, "rb");
    if (!fp) {
        printf("Error: fopen(%s) error number %d, %s.\n", FILEPATH, errno, strerror(errno));
        exit(1);
    }
    struct stat sb;
    if (stat(FILEPATH, &sb) == -1) {
        printf("stat error\n");
        exit(1);
    }

    fread(PROGRAM_START_ADDR, sb.st_size, 1, fp);

    fclose(fp);

    printf("Loaded %s\n", arg);

}