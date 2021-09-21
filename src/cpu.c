#include <cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <display.h>
#include <input.h>
#include <timer.h>
#include <arpa/inet.h>
#include <settings.h>


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
    uint16_t I;  // Index register used to point to locations in memory
} reg;


void init_cpu(void) {
    pc = PROGRAM_START_ADDR;
}

// Read an instruction that the program counter is pointing to and returns it.
uint16_t fetch(void) {
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
    uint8_t  nib1       = (opcode >> 12) & 0xf;
    uint8_t  nib2       = (opcode >> 8)  & 0xf;
    uint8_t  nib3       = (opcode >> 4)  & 0xf;
    uint8_t  nib4       =  opcode        & 0xf;
    uint8_t  last_two   =  opcode        & 0x00ff;
    uint16_t last_three =  opcode        & 0x0fff;

    // https://en.wikipedia.org/wiki/CHIP-8#Opcode_table
    switch (nib1) {
        case 0x0:
            if (nib2 == 0 && nib3 == 0 && nib4 == 0) {
                printf("Possibly reading outside of memory space.\n");
            }
            if (nib2 == 0x0 && nib3 == 0xE && nib4 == 0x0) {// clear screen
                clear_screen();
            } else if (nib3 == 0xE && nib4 == 0xE) { // Return from subroutine
                pc = stack_pop();
            }
            break;
        case 0x1: // jump
            pc = &MEMORY[last_three];
            break;
        case 0x2: // Call subroutine
            stack_push(pc);
            pc = &MEMORY[last_three];
            break;
        case 0x3: // Skip equal
            if (DATA_AT_REG(nib2) == last_two) {
                pc = pc + 2;
            }
            break;
        case 0x4: // Skip not equal
            if (DATA_AT_REG(nib2) != last_two) {
                pc = pc + 2;
            }
            break;
        case 0x5: // Skip if two registers are equal
            if (DATA_AT_REG(nib2) == DATA_AT_REG(nib3)) {
                pc = pc + 2;
            }
            break;
        case 0x6: // Set register
            DATA_AT_REG(nib2) = last_two;
            break;
        case 0x7: // add a value to register VX
            DATA_AT_REG(nib2) = DATA_AT_REG(nib2) + last_two;
            break;
        case 0x8:
            switch (nib4) {
                case 0x0: // Set register to another register
                    DATA_AT_REG(nib2) = DATA_AT_REG(nib3);
                    break;
                case 0x1: // Binary OR 
                    DATA_AT_REG(nib2) = DATA_AT_REG(nib2) | DATA_AT_REG(nib3);
                    break;
                case 0x2: // Binary AND
                    DATA_AT_REG(nib2) = DATA_AT_REG(nib2) & DATA_AT_REG(nib3);
                    break;
                case 0x3: // Binary XOR
                    DATA_AT_REG(nib2) = DATA_AT_REG(nib2) ^ DATA_AT_REG(nib3);
                    break;
                case 0x4: // Addition with carry flag
                    // Check for overflow
                    if (DATA_AT_REG(nib3) + DATA_AT_REG(nib2) > 255) {
                        reg.VF = 0x01;
                    } else {
                        reg.VF = 0x00;
                    }
                    DATA_AT_REG(nib2) = DATA_AT_REG(nib2) + DATA_AT_REG(nib3);
                    break;
                case 0x5: // Subtract with carry flag (X = X - Y)
                    if (DATA_AT_REG(nib2) >= DATA_AT_REG(nib3)) {
                        reg.VF = 0x01;
                    } else {
                        reg.VF = 0x00;
                    }
                    DATA_AT_REG(nib2) = DATA_AT_REG(nib2) - DATA_AT_REG(nib3);
                    break;
                case 0x6: // Shift
                    reg.VF = (DATA_AT_REG(nib2) & 0x01);
                    DATA_AT_REG(nib2) = DATA_AT_REG(nib3) >> 1;
                    break;
                case 0x7: // Subtract with carry flag (X = Y - X)
                    if (DATA_AT_REG(nib2) < DATA_AT_REG(nib3)) {
                        reg.VF = 0x01;
                    }
                    else {
                        reg.VF = 0x00;
                    }
                    DATA_AT_REG(nib2) = DATA_AT_REG(nib3) - DATA_AT_REG(nib2);
                    break;
                case 0xE:
                    if ((DATA_AT_REG(nib2) & 0x80) > 0) {
                        reg.VF = 1;
                    } else {
                        reg.VF = 0;
                    }
                    DATA_AT_REG(nib2) = DATA_AT_REG(nib3) << 1;
                    break;
            }
            break;
        case 0x9: // Skip if two registers are not equal
            if (DATA_AT_REG(nib2) != DATA_AT_REG(nib3)) {
                pc = pc + 2;
            }
            break;
        case 0xA: // Set index register
            reg.I = last_three;
            break;
        case 0xB: // Jump with offset
            pc = MEMORY_ADDR + (DATA_AT_REG(0) + last_three);
            break;
        case 0xC: // Random
            DATA_AT_REG(nib2) = (rand() % 0xFF) & last_two;
            break;
        case 0xD: // Display (DXYN)
            {   
                uint8_t x = DATA_AT_REG(nib2) % PIXELS_WIDTH;
                uint8_t y = DATA_AT_REG(nib3) % PIXELS_HEIGHT;
                uint8_t n = nib4;
                uint16_t addr = reg.I; // Pull the data out of index register
                reg.VF = draw_from_mem(addr, x, y, n);
            }
            break;
        case 0xE: // Skip if key matching register is being pressed 
            if (nib3 == 0x9 && nib4 == 0xE) {
                if (get_currently_pressed() == DATA_AT_REG(nib2)) {
                    pc = pc + 2;
                } // Skip if key matching register is not being pressed 
            } else if (nib3 == 0xA && nib4 == 0x1) {
                if (get_currently_pressed() != DATA_AT_REG(nib2)) {
                    pc = pc + 2;
                }
            }
            break;
        case 0xF:
            switch (last_two) {
                case 0x07:
                    DATA_AT_REG(nib2) = DELAY_TIMER;
                    break;
                case 0x15:
                    DELAY_TIMER = DATA_AT_REG(nib2);
                    break;
                case 0x18:
                    SOUND_TIMER = DATA_AT_REG(nib2);
                    break;
                case 0x1E:
                    reg.I = reg.I + DATA_AT_REG(nib2);
                    break;
                case 0x0A:
                    if (get_currently_pressed() == 0xDEADBEEF) {
                        pc = pc - 2;
                    } else {
                        DATA_AT_REG(nib2) = get_currently_pressed();
                    }
                    break;
                case 0x29:
                    reg.I = 0x50 + (5*DATA_AT_REG(nib2));
                    break;
                case 0x33:
                    MEMORY[reg.I] = DATA_AT_REG(nib2) / 100;
                    MEMORY[reg.I+1] = (DATA_AT_REG(nib2) % 100) / 10;
                    MEMORY[reg.I+2] = (DATA_AT_REG(nib2) % 10);
                    break;
                case 0x55:
                    for (int i = 0; i <= nib2; i++) {
                        MEMORY[reg.I + i] = DATA_AT_REG(i);
                    }
                    break;
                case 0x65:
                    for (int i = 0; i <= nib2; i++) {
                        DATA_AT_REG(i) = MEMORY[reg.I + i];
                    }
                    break;
            }
            break;
    }
}

void cpu_cycle(void) {
    uint16_t opcode = fetch();
    decode_and_execute(opcode);
}