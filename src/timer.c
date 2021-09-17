#include <timer.h>
#include <stdio.h>

uint8_t delay_timer = 0;
uint8_t sound_timer = 0;


void init_timers(void) {
}

static void decrement_8bit_timer(uint8_t* t) {
    if (t > 0) {
        *t--;
    }
}


// Decrements both bit timers 60 times per second 
void update_timers(void) {
    decrement_8bit_timer(&delay_timer);
    decrement_8bit_timer(&sound_timer);
    // Store the last time the timers got changed.
}
