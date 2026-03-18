#include "timer.h"

// Pi 4 timer base
#define TIMER_BASE_PI4      0xFE003000

// Pi 5 timer base (ARM local timer)
#define TIMER_BASE_PI5      0x107C000000ULL

// Use Pi 4 address by default
// Note: On Pi 5, the timer peripheral may not be directly accessible
// The mailbox framebuffer init should still work though
static volatile unsigned long long timer_base = TIMER_BASE_PI4;

unsigned long get_timer_count(void) {
    // Simplified timer that won't crash on Pi 5
    // Returns a simple counter that increments
    static unsigned long counter = 0;
    counter += 100;  // Simulate time passing
    return counter;
}

void delay_microseconds(unsigned int us) {
    // Simple delay loop that doesn't depend on hardware timer
    volatile unsigned int count = us * 10;
    while (count--);
}

void delay_milliseconds(unsigned int ms) {
    delay_microseconds(ms * 1000);
}
