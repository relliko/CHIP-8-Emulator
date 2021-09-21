#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mem.h>

// Initializes the system's memory
// Returns 1 upon success
void init_mem(void) {
    memset(MEMORY, 0, sizeof(MEMORY));
    MEMORY_ADDR = &MEMORY[0];
    FONT_ADDR = MEMORY_ADDR + 0x50;
    PROGRAM_START_ADDR = MEMORY_ADDR + 0x200;
    MEMORY_END_ADDR = MEMORY_ADDR + RAM_SIZE;
    stack.height = 0;
}

// Pushes 16 bits of data onto the system's stack.
void stack_push(uint8_t* data) {
    if (stack.height >= STACK_SIZE) {
        printf("ERROR: Attempt to push to stack when stack is full.\n");
        exit(1);
    }
    stack.stk[stack.height] = data;
    stack.height++;
}

// Pops 16 bits of data off the stack and returns it.
// Returns -1 if there was a failure
uint8_t* stack_pop(void) {
    if (stack.height == 0) {
        printf("ERROR: Attempt to pop from stack when stack is empty.\n");
        exit(1);
    }
    uint8_t* ret = stack.stk[stack.height-1];
    stack.height--;
    return ret;
}

uint8_t* stack_peek(void) {
    return stack.stk[stack.height];
}