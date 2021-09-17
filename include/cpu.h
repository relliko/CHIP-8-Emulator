#include <mem.h>
#include <stdint.h>


#define IPS 700 // Instructions per second

uint8_t* pc; // Program counter 

void init_cpu(void);
void cpu_cycle(void);

uint16_t I; // Index register used to point to locations in memory
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