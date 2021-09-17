#include <timer.h>
#include <stdio.h>

uint8_t delay_timer = 0;
uint8_t sound_timer = 0;

struct timeval prev;
struct timeval now;

int test = 0;

void init_timers(void) {
    gettimeofday(&prev, NULL);
}

static void decrement_8bit_timer(uint8_t* t) {
    if (t > 0) {
        *t--;
    }
}


// Decrements both bit timers 60 times per second 
void update_timers(void) {
    gettimeofday(&now, NULL);
    // printf("%ld\n", now.tv_usec);
    // printf("%ld\n", prev.tv_usec);
    double ms = (((now.tv_sec * 1000000) + now.tv_usec) - ((prev.tv_sec * 1000000) + prev.tv_usec)) / (double) 1000;
    if (ms < 16.6666) {
        //printf("%f\n", ms);
        // Skip execution
        return;
    } 
    if (test >= 60) {
        printf("one second\n");
        test = 0;
    }
    test++;
    //printf("%f\n", ms);
    decrement_8bit_timer(&delay_timer);
    decrement_8bit_timer(&sound_timer);
    // Store the last time the timers got changed.
    gettimeofday(&prev, NULL);
}
