#ifndef GPIO_H
#define GPIO_H

void gpio_set_input(unsigned int pin);
void gpio_set_pullup(unsigned int pin);
int gpio_read(unsigned int pin);
void input_init(void);
int button_up(void);
int button_down(void);
int button_left(void);
int button_right(void);
int button_fire(void);

#endif
