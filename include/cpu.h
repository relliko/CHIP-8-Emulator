#include <mem.h>
#include <stdint.h>
#include <settings.h>

#define IPS 700 // Instructions per second
#define DATA_AT_REG(reg,x) (*(&reg.V0 + x))


void init_cpu(void);
void cpu_cycle(void);
