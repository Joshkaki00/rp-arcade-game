#include "timer.h"

#define TIMER_BASE      0xFE003000

static volatile unsigned int *timer = (unsigned int*)TIMER_BASE;

unsigned long get_timer_count(void) {
    unsigned int high = timer[2];
    unsigned int low = timer[1];
    return ((unsigned long)high << 32) | low;
}

void delay_microseconds(unsigned int us) {
    unsigned long start = get_timer_count();
    while (get_timer_count() - start < us);
}

void delay_milliseconds(unsigned int ms) {
    delay_microseconds(ms * 1000);
}
