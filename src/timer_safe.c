#include "timer.h"

// Safe timer implementation that won't hang
unsigned long get_timer_count(void) {
    // Simple software counter instead of hardware timer
    static unsigned long counter = 0;
    counter += 100;
    return counter;
}

void delay_microseconds(unsigned int us) {
    // Software delay
    volatile unsigned int count = us * 10;
    while (count--);
}

void delay_milliseconds(unsigned int ms) {
    delay_microseconds(ms * 1000);
}
