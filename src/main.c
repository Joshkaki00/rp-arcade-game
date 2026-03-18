#include "framebuffer.h"
#include "gpio.h"
#include "timer.h"
#include "game.h"

void main(void) {
    if (!framebuffer_init()) {
        while (1);
    }
    
    input_init();
    game_init();
    
    unsigned long last_frame = get_timer_count();
    const unsigned long frame_time = 16666;
    
    while (1) {
        unsigned long now = get_timer_count();
        
        if (now - last_frame >= frame_time) {
            game_update();
            game_render();
            last_frame = now;
        }
    }
}
