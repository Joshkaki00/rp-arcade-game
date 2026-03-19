#include "gpio.h"

// Safe GPIO - no hardware access, always returns "not pressed"
void gpio_set_input(unsigned int pin) {
    (void)pin;
}

void gpio_set_pullup(unsigned int pin) {
    (void)pin;
}

int gpio_read(unsigned int pin) {
    (void)pin;
    return 1; // Not pressed
}

void input_init(void) {
    // Safe - does nothing
}

int button_up(void) { return 0; }
int button_down(void) { return 0; }
int button_left(void) { return 0; }
int button_right(void) { return 0; }
int button_fire(void) { return 0; }
