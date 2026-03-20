#include "framebuffer.h"
#include "gpio.h"
#include "timer.h"

void main(void) {
    if (!framebuffer_init()) {
        while (1);
    }
    
    // Game objects
    int player_x = get_screen_width() / 2;
    int player_y = get_screen_height() - 50;
    
    int enemy_x[5] = {100, 300, 500, 700, 900};
    int enemy_y[5] = {0, 50, 100, 150, 200};
    int enemy_active[5] = {1, 1, 1, 1, 1};  // All active from start!
    
    while (1) {
        // Clear screen
        clear_screen(COLOR_BLACK);
        
        // Draw player (green)
        draw_rect(player_x, player_y, 20, 20, COLOR_GREEN);
        
        // Draw and move enemies (red)
        for (int i = 0; i < 5; i++) {
            if (enemy_active[i]) {
                draw_rect(enemy_x[i], enemy_y[i], 20, 20, COLOR_RED);
                
                // Move down
                enemy_y[i] += 2;
                
                // Respawn at top when off screen
                if (enemy_y[i] > get_screen_height()) {
                    enemy_y[i] = 0;
                    enemy_x[i] = (enemy_x[i] + 123) % (get_screen_width() - 40);
                }
            }
        }
        
        // Software delay
        volatile int delay;
        for (delay = 0; delay < 100000; delay++);
    }
}
