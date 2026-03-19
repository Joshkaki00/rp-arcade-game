#include "framebuffer.h"

void main(void) {
    if (!framebuffer_init()) {
        while (1);
    }
    
    // Simple game loop without timer or GPIO
    int player_x = get_screen_width() / 2;
    int player_y = get_screen_height() - 50;
    int enemy_x = 100;
    int enemy_y = 0;
    
    int frame = 0;
    
    while (1) {
        // Clear screen
        clear_screen(COLOR_BLACK);
        
        // Draw player (green)
        draw_rect(player_x, player_y, 20, 20, COLOR_GREEN);
        
        // Draw enemy (red) - moves down automatically
        draw_rect(enemy_x, enemy_y, 20, 20, COLOR_RED);
        
        // Move enemy down
        enemy_y += 2;
        if (enemy_y > get_screen_height()) {
            enemy_y = 0;
            enemy_x = (frame * 37) % (get_screen_width() - 40);
        }
        
        // Software delay (no timer needed)
        volatile int delay;
        for (delay = 0; delay < 100000; delay++);
        
        frame++;
    }
}
