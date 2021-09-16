#include <stdio.h>
#include <mem.h>
#include <font.h>
#include <debug.h>
#include <display.h>
#include <input.h>

int main(int argc, char **argv) {
    printf("Booting...\n");
    init_mem();
    load_font();
    // print_memory(80, 80);
    // test_stack();
    init_display();

    // Main game loop
    while (1) {
        handle_input_events();
        // Update loop
        render();
    }

    cleanup_display();
    return 0;
}