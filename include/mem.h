#include <stdint.h>

// CHIP-8 has direct access to up to 4KB of RAM
#define RAM_SIZE 4096 // bytes
#define STACK_SIZE 16 // 16 two-byte entries

// TODO: This could be refactored into a struct
uint8_t MEMORY[RAM_SIZE];
uint8_t* MEMORY_ADDR;
uint8_t* PROGRAM_START_ADDR;
uint8_t* MEMORY_END_ADDR;

struct stack_t {
    uint16_t stk[STACK_SIZE];
    uint8_t height;
} stack;


void init_mem();
int stack_push(uint16_t data);
uint16_t stack_pop(void);
uint16_t stack_peek(void);