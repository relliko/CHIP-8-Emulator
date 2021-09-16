#include <stdio.h>
#include <cpu.h>
#include <font.h>
#include <debug.h>
#include <display.h>
#include <input.h>
#include <timer.h>

int main(int argc, char **argv) {
    printf("Booting...\n");
    init_mem();
    init_cpu();
    load_font();
    // print_memory(80, 80);
    // test_stack();
    init_display();

    // Main game loop
    while (1) {
        update_timers();
        handle_input_events();
        // TODO: Main update loop

        render();
    }

    cleanup_display();
    return 0;
}