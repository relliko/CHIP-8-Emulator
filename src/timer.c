#include <timer.h>
#include <stdio.h>

uint8_t delay_timer = 0;
uint8_t sound_timer = 0;


void init_timers(void) {
}


static void decrement_8bit_timer(uint8_t* t) {
    if (t > 0) {
        *t = *t - 1;
    }
}


// Decrements both bit timers 60 times per second 
void update_timers(void) {
    decrement_8bit_timer(&DELAY_TIMER);
    decrement_8bit_timer(&SOUND_TIMER);
}
