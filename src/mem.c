#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

// Initializes the system's memory
// Returns 1 upon success
void init_mem(void) {
    MEMORY_ADDR = &MEMORY[0];
    FONT_ADDR = MEMORY_ADDR + 0x50;
    PROGRAM_START_ADDR = MEMORY_ADDR + 0x500;
    MEMORY_END_ADDR = MEMORY_ADDR + RAM_SIZE;
    stack.height = 0;
}

// Pushes 16 bits of data onto the system's stack.
int stack_push(uint16_t data) {
    if (stack.height >= STACK_SIZE) {
        printf("ERROR: Attempt to push to stack when stack is full.\n");
        return -1;
    }
    stack.stk[stack.height] = data;
    stack.height++;
    return 0;
}

// Pops 16 bits of data off the stack and returns it.
// Returns -1 if there was a failure
uint16_t stack_pop(void) {
    if (stack.height == 0) {
        printf("ERROR: Attempt to pop from stack when stack is empty.\n");
        return -1;
    }
    uint16_t ret = stack.stk[stack.height];
    stack.height--;
    return ret;
}

uint16_t stack_peek(void) {
    return stack.stk[stack.height];
}