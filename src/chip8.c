#include <stdio.h>
#include <cpu.h>
#include <font.h>
#include <debug.h>
#include <display.h>
#include <input.h>
#include <timer.h>
#include <file.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: chip8 rom_filename");
        exit(EXIT_FAILURE);
    }
    printf("Booting...\n");
    init_mem();
    init_cpu();
    init_timers();
    load_font();
    //print_memory(80, 80);
    //test_stack();
    init_display();
    load_ROM(argv[1]);

    // Main loop
    while (1) {
        update_timers();
        handle_input_events();
        
        cpu_cycle();
        render();
    }

    cleanup_display();
    return 0;
}