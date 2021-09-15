#include <stdio.h>
#include <mem.h>
#include <font.h>
#include <debug.h>
#include <display.h>

int main(int argc, char **argv) {
    printf("Booting...\n");
    init_mem();
    load_font();
    // print_memory(80, 80);
    // test_stack();
    init_SDL();
    return 0;
}