#include <cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <display.h>
#include <arpa/inet.h>


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
    uint8_t  last_two   = opcode & 0x00ff;
    uint16_t last_three = opcode & 0x0fff;

    // https://en.wikipedia.org/wiki/CHIP-8#Opcode_table
    switch (nib1) {
        case 0x0:
            if (nib2 == 0 && nib3 == 0 && nib4 == 0)
                printf("Possibly reading outside of memory space.\n");
            if (nib2 == 0x0 && nib3 == 0xE && nib4 == 0x0) // clear screen
                clear_screen();
            else if (nib3 == 0xE && nib4 == 0xE)// Return from subroutine
                pc = stack_pop();
            break;
        case 0x1: // jump
            pc = MEMORY_ADDR + last_three;
            break;
        case 0x2: // Call subroutine
            stack_push(pc);
            pc = MEMORY_ADDR + (opcode & 0x0FFF);
            break;
        case 0x3: // Skip equal
            if (DATA_AT_REG(reg, nib2) == last_two)
                pc = pc + 2;
            break;
        case 0x4: // Skip not equal
            if (DATA_AT_REG(reg, nib2) != last_two)
                pc = pc + 2;
            break;
        case 0x5: // Skip if two registers are equal
            if (DATA_AT_REG(reg, nib2) == DATA_AT_REG(reg, nib3))
                pc = pc + 2;
            break;
        case 0x6: // Set register
            DATA_AT_REG(reg, nib2) = last_two;
            break;
        case 0x7: // add a value to register VX
            DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib2) + last_two;
            break;
        case 0x8:
            switch (nib4) {
                case 0x0: // Set register to another register
                    DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib3);
                    break;
                case 0x1: // Binary OR 
                    DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib2) | DATA_AT_REG(reg, nib3);
                    break;
                case 0x2: // Binary AND
                    DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib2) & DATA_AT_REG(reg, nib3);
                    break;
                case 0x3: // Binary XOR
                    DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib2) ^ DATA_AT_REG(reg, nib3);
                    break;
                case 0x4: // Addition with carry flag
                    DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib2) + DATA_AT_REG(reg, nib3);
                    // Check for overflow
                    if (DATA_AT_REG(reg, nib3) > DATA_AT_REG(reg, nib2))
                        reg.VF = 1;
                    else
                        reg.VF = 0;
                    break;
                case 0x5: // Subtract with carry flag (X = X - Y)
                    DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib2) - DATA_AT_REG(reg, nib3);
                    if (DATA_AT_REG(reg, nib2) < DATA_AT_REG(reg, nib3))
                        reg.VF = 1;
                    else
                        reg.VF = 0;
                    break;
                case 0x6: // Shift
                    if (!SUPER_CHIP)
                        DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib3);
                    DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib2) >> 1;
                    break;
                case 0x7: // Subtract with carry flag (X = Y - X)
                    DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib3) - DATA_AT_REG(reg, nib2);
                    if (DATA_AT_REG(reg, nib3) < DATA_AT_REG(reg, nib2))
                        reg.VF = 1;
                    else
                        reg.VF = 0;
                    break;
                case 0xE:
                    if (!SUPER_CHIP)
                        DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib3);
                    DATA_AT_REG(reg, nib2) = DATA_AT_REG(reg, nib2) << 1;
                    break;
            }
            break;
        case 0x9: // Skip if two registers are not equal
            if (DATA_AT_REG(reg, nib2) != DATA_AT_REG(reg, nib3))
                pc = pc + 2;
            break;
        case 0xA: // Set index register
            reg.I = last_three;
            break;
        case 0xB:
            break;
        case 0xC:
            break;
        case 0xD: // Display 
            {   
                uint8_t x = DATA_AT_REG(reg, nib2);
                uint8_t y = DATA_AT_REG(reg, nib3);
                uint8_t n = nib4;
                uint16_t addr = reg.I; // Pull the data out of index register
                int res = draw_from_mem(addr, n, x, y);
                // Set flag register to 1
                if (res == 1)
                    reg.VF = 1;
            }
            break;
        case 0xE:
            break;
        case 0xF:
            break;
    }
}

void cpu_cycle(void) {
    uint16_t opcode = fetch();
    decode_and_execute(opcode);
}