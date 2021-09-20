#include <file.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

// Loads a ROM into memory at 0x200
void load_ROM() {
    FILE* fp;
    char* filepath = "./ROM/PONG";
    fp = fopen(filepath, "rb");
    if (!fp) {
        printf("Error: fopen(%s) error number %d, %s.\n", filepath, errno, strerror(errno));
        exit(1);
    }
    struct stat sb;
    if (stat(filepath, &sb) == -1) {
        printf("stat error\n");
        exit(1);
    }

    fread(PROGRAM_START_ADDR, sb.st_size, 1, fp);

    fclose(fp);

    printf("Loaded ROM\n");

}