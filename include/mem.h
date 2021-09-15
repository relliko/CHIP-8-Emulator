#include <stdint.h>

// CHIP-8 has direct access to up to 4KB of RAM
#define RAM_SIZE 4096 // bytes
#define STACK_SIZE 16 // 16 two-byte entries

uint8_t MEMORY[RAM_SIZE];
uint8_t* MEMORY_ADDR;

struct stack_t {
    uint16_t stk[STACK_SIZE];
    uint8_t height;
} stack;


void init_mem();
int stack_push(uint16_t data);
uint16_t stack_pop(void);
uint16_t stack_peek(void);