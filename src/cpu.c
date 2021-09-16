#include <cpu.h>


uint8_t* pc;

void init_cpu(void) {
    pc = MEMORY_ADDR + 0x500;
}

// Read an instruction that the program counter register is pointing to.
void fetch(void) {

}

// 
void decode(void) {

}