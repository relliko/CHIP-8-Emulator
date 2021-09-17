#include <stdio.h>
#include <mem.h>
#include <debug.h>

// Prints n bytes of system's memory in binary from the offset byte start
void print_memory(short start, short n) {
    printf("Printing %d bytes of system memory:\n", n);
    if (start > RAM_SIZE || n > RAM_SIZE) {
        printf("Error: start or n cannot exceed maximum number of bytes in memory");
        return;
    }
    short p1 = start;

    if ((p1 + n) > RAM_SIZE) {
        printf("Error: given parameters exceed bounds of system memory");
        return;
    }

    for (int i = p1; i < p1 + n; i++) {
        if (i % 2 == 0 && i == p1) {
            printf("----- ---- ----");
        }
        if (i % 2 == 0) {
            printf(" | %#04x: "BYTE_TO_BINARY_PATTERN"\n", (uint8_t) i, BYTE_TO_BINARY(MEMORY[i]));
        } else {
            printf("%#04x: "BYTE_TO_BINARY_PATTERN, (uint8_t) i, BYTE_TO_BINARY(MEMORY[i]));
        }
        if (i == p1 + n - 1 && i % 2 == 1) {
            printf(" | ----- ---- ----\n");
        }
    }
}

void print_pixels_array(uint8_t arr[32][64]) {
    printf("Printing pixels array\n");
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            printf(" | %#04x: "BYTE_TO_BINARY_PATTERN"\n", (uint8_t) x/8, BYTE_TO_BINARY(arr[y/8][x/8]));
        }
    }
    printf("Printing pixels array finished\n\n");
}

// fills the stack then pops 
void test_stack() {
    int c = 0;
    while (c < STACK_SIZE) {
        stack_push((uint16_t) c);
        c++;
    }
    
    while (c > 0) {
        uint16_t data = stack_pop();
        printf("%d\n", data);
        c--;
    }
}