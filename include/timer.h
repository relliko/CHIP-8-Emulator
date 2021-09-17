#include <stdint.h>
#include <sys/time.h>

uint8_t delay_timer;
uint8_t sound_timer;

// struct timeval {
//     long tv_sec;
//     long tv_usec;
// }

void update_timers(void);
void init_timers(void);