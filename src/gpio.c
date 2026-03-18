#include "gpio.h"
#include "timer.h"

#define GPIO_BASE       0xFE200000

#define GPFSEL0         ((volatile unsigned int*)(GPIO_BASE + 0x00))
#define GPFSEL1         ((volatile unsigned int*)(GPIO_BASE + 0x04))
#define GPSET0          ((volatile unsigned int*)(GPIO_BASE + 0x1C))
#define GPCLR0          ((volatile unsigned int*)(GPIO_BASE + 0x28))
#define GPLEV0          ((volatile unsigned int*)(GPIO_BASE + 0x34))
#define GPPUD           ((volatile unsigned int*)(GPIO_BASE + 0x94))
#define GPPUDCLK0       ((volatile unsigned int*)(GPIO_BASE + 0x98))

void gpio_set_input(unsigned int pin) {
    unsigned int reg = pin / 10;
    unsigned int shift = (pin % 10) * 3;
    unsigned int value = *(GPFSEL0 + reg);
    value &= ~(7 << shift);
    *(GPFSEL0 + reg) = value;
}

void gpio_set_pullup(unsigned int pin) {
    *GPPUD = 2;
    delay_microseconds(150);
    *GPPUDCLK0 = (1 << pin);
    delay_microseconds(150);
    *GPPUD = 0;
    *GPPUDCLK0 = 0;
}

int gpio_read(unsigned int pin) {
    return (*GPLEV0 & (1 << pin)) ? 1 : 0;
}

void input_init(void) {
    gpio_set_input(17);
    gpio_set_input(27);
    gpio_set_input(22);
    gpio_set_input(23);
    gpio_set_input(24);
    
    gpio_set_pullup(17);
    gpio_set_pullup(27);
    gpio_set_pullup(22);
    gpio_set_pullup(23);
    gpio_set_pullup(24);
}

int button_up(void) { return !gpio_read(17); }
int button_down(void) { return !gpio_read(27); }
int button_left(void) { return !gpio_read(22); }
int button_right(void) { return !gpio_read(23); }
int button_fire(void) { return !gpio_read(24); }
