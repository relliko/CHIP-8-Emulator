#include <timer.h>

uint8_t delay_timer = 0;
uint8_t sound_timer = 0;

static void decrement_8bit_timer(uint8_t* t) {
    *t--;
}

void update_timers(void) {
    if (delay_timer > 0) {
        decrement_8bit_timer(&delay_timer);
    }
    if (sound_timer > 0) {
        decrement_8bit_timer(&sound_timer);
    }
}