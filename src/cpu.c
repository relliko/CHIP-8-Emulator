#include <cpu.h>
#include <stdio.h>
#include <stdlib.h>


uint8_t* pc;

void init_cpu(void) {
    pc = PROGRAM_START_ADDR;
}

// Read an instruction that the program counter is pointing to and returns it.
uint16_t fetch(void) {
    if (pc == MEMORY_END_ADDR) {
        pc = PROGRAM_START_ADDR; 
        printf("End\n");
    }
    uint8_t part1 = *pc;
    pc = pc + 1;
    uint8_t part2 = *pc;
    pc = pc + 1;
    uint16_t opcode = (part1 << 8) | (part2);
    return opcode;
}


void decode(uint16_t op) {
}

void cpu_cycle(void) {
    uint16_t opcode = fetch();
    decode(opcode);
}