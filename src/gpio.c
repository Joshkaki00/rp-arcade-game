#include "gpio.h"
#include "timer.h"

// Raspberry Pi 4 GPIO base address
#define GPIO_BASE_PI4       0xFE200000

// Raspberry Pi 5 RP1 GPIO base address (via PCIe)
#define GPIO_BASE_PI5       0x1F000D0000ULL

// PCIe controller base for RP1 access on Pi 5
#define PCIE_REG_BASE       0x1F00000000ULL

// Current GPIO base (set at runtime)
static volatile unsigned long long gpio_base = GPIO_BASE_PI4;
static int is_rpi5 = 0;

#define GPFSEL0         ((volatile unsigned int*)(gpio_base + 0x00))
#define GPFSEL1         ((volatile unsigned int*)(gpio_base + 0x04))
#define GPSET0          ((volatile unsigned int*)(gpio_base + 0x1C))
#define GPCLR0          ((volatile unsigned int*)(gpio_base + 0x28))
#define GPLEV0          ((volatile unsigned int*)(gpio_base + 0x34))
#define GPPUD           ((volatile unsigned int*)(gpio_base + 0x94))
#define GPPUDCLK0       ((volatile unsigned int*)(gpio_base + 0x98))

// Pi 5 uses different pull-up/down registers
#define GPIO_PUP_PDN_CNTRL_REG0  ((volatile unsigned int*)(gpio_base + 0xE4))

void gpio_set_input(unsigned int pin) {
    unsigned int reg = pin / 10;
    unsigned int shift = (pin % 10) * 3;
    unsigned int value = *(GPFSEL0 + reg);
    value &= ~(7 << shift);
    *(GPFSEL0 + reg) = value;
}

void gpio_set_pullup(unsigned int pin) {
    if (is_rpi5) {
        // Pi 5 uses different pull-up/down control
        unsigned int reg = pin / 16;
        unsigned int shift = (pin % 16) * 2;
        volatile unsigned int *pup_pdn = GPIO_PUP_PDN_CNTRL_REG0 + reg;
        unsigned int value = *pup_pdn;
        value &= ~(3 << shift);
        value |= (1 << shift);  // 01 = pull-up
        *pup_pdn = value;
    } else {
        // Pi 4 and earlier
        *GPPUD = 2;
        delay_microseconds(150);
        *GPPUDCLK0 = (1 << pin);
        delay_microseconds(150);
        *GPPUD = 0;
        *GPPUDCLK0 = 0;
    }
}

int gpio_read(unsigned int pin) {
    return (*GPLEV0 & (1 << pin)) ? 1 : 0;
}

// Detect Raspberry Pi version
static void detect_pi_version(void) {
    // Try to read from Pi 5 RP1 GPIO address
    // Note: This is a simplified detection - in reality, Pi 5 requires
    // PCIe initialization before RP1 peripherals are accessible
    volatile unsigned int *test_addr = (volatile unsigned int*)GPIO_BASE_PI5;
    
    // For now, assume Pi 4 by default
    // TODO: Implement proper PCIe initialization for Pi 5
    gpio_base = GPIO_BASE_PI4;
    is_rpi5 = 0;
    
    // The proper way would be to:
    // 1. Initialize PCIe controller
    // 2. Map RP1 peripheral space
    // 3. Access GPIO through RP1
}

void input_init(void) {
    detect_pi_version();
    
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
