#include "framebuffer.h"
#include "gpio.h"
#include "timer.h"
#include "game.h"

void main(void) {
    if (!framebuffer_init()) {
        while (1);
    }
    
    // Draw a test pattern FIRST to prove framebuffer works
    // Red square top-left
    draw_rect(0, 0, 100, 100, COLOR_RED);
    // Green square top-right  
    draw_rect(get_screen_width() - 100, 0, 100, 100, COLOR_GREEN);
    // Blue square bottom-left
    draw_rect(0, get_screen_height() - 100, 100, 100, COLOR_BLUE);
    // Yellow square bottom-right
    draw_rect(get_screen_width() - 100, get_screen_height() - 100, 100, 100, COLOR_YELLOW);
    
    // White square center
    draw_rect(get_screen_width()/2 - 50, get_screen_height()/2 - 50, 100, 100, COLOR_WHITE);
    
    // Now try to run the game
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
