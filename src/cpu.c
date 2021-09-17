#include <cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <display.h>


uint8_t* pc;
struct registers {
    // General-purpose registers
    uint8_t V0;
    uint8_t V1;
    uint8_t V2;
    uint8_t V3;
    uint8_t V4;
    uint8_t V5;
    uint8_t V6;
    uint8_t V7;
    uint8_t V8;
    uint8_t V9;
    uint8_t VA;
    uint8_t VB;
    uint8_t VC;
    uint8_t VD;
    uint8_t VE;
    uint8_t VF;  // flag register
    uint16_t I; // Index register used to point to locations in memory
} reg;


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

// Decodes an opcode and executes the instruction.
void decode_and_execute(uint16_t opcode) {
    // Extract each nibble from the 2 byte opcode
    uint8_t nib1 = (opcode >> 12) & 0xf;
    uint8_t nib2 = (opcode >> 8)  & 0xf;
    uint8_t nib3 = (opcode >> 4)  & 0xf;
    uint8_t nib4 =  opcode        & 0xf;
    //printf("%d %d %d\n", nib2, nib3, nib4);

    switch (nib1) {
        case 0x0: // clear screen
            clear_screen();
            break;
        case 0x1: // jump
            pc = MEMORY_ADDR + ((nib2 << 8) + (nib3 << 4) + nib4);
            break;
        case 0x2:
            break;
        case 0x3:
            break;
        case 0x4:
            break;
        case 0x5:
            break;
        case 0x6: // Set register
            // Assign the register VX where X is the data in nib2 
            // the data in the last 2 nibbles in the opcode
            DATA_AT_REG(reg, nib2) = ((nib3 << 4) + nib4);
            break;
        case 0x7: // add a value to register VX
            DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib2) + ((nib3 << 4) + nib4);
            break;
        case 0x8:
            break;
        case 0x9:
            break;
        case 0xA: // Set index register
            *(&reg.I) = ((nib2 << 8) + (nib3 << 4) + nib4);
            break;
        case 0xB:
            break;
        case 0xC:
            break;
        case 0xD:
            break;
        case 0xE:
            break;
        case 0xF:
            break;
    }
}

void cpu_cycle(void) {
    uint16_t opcode = fetch();
    // uint16_t test = 0xA111;
    // decode_and_execute(test);
    // uint16_t test2 = 0x7101;
    // decode_and_execute(test2);
    // decode_and_execute(opcode);
}