#include "framebuffer.h"

// Minimal test main - just initialize framebuffer and show colors
void main(void) {
    // Try to initialize framebuffer
    if (!framebuffer_init()) {
        // If init fails, hang forever
        while (1) {
            // Blink pattern using CPU cycles (no timer needed)
            volatile int i;
            for (i = 0; i < 10000000; i++);
        }
    }
    
    // Success! Show a test pattern
    // Fill screen with different colors in bands
    unsigned int colors[] = {
        COLOR_RED,
        COLOR_GREEN,
        COLOR_BLUE,
        COLOR_YELLOW,
        COLOR_CYAN,
        COLOR_MAGENTA,
        COLOR_WHITE
    };
    
    unsigned int height = get_screen_height();
    unsigned int band_height = height / 7;
    
    for (int i = 0; i < 7; i++) {
        draw_rect(0, i * band_height, get_screen_width(), band_height, colors[i]);
    }
    
    // Hang forever showing the pattern
    while (1);
}
