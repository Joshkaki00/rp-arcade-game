#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#define RGB(r, g, b) (((r) << 16) | ((g) << 8) | (b))

#define COLOR_BLACK     RGB(0, 0, 0)
#define COLOR_WHITE     RGB(255, 255, 255)
#define COLOR_RED       RGB(255, 0, 0)
#define COLOR_GREEN     RGB(0, 255, 0)
#define COLOR_BLUE      RGB(0, 0, 255)
#define COLOR_YELLOW    RGB(255, 255, 0)
#define COLOR_CYAN      RGB(0, 255, 255)
#define COLOR_MAGENTA   RGB(255, 0, 255)

int framebuffer_init(void);
void draw_pixel(int x, int y, unsigned int color);
void draw_rect(int x, int y, int w, int h, unsigned int color);
void clear_screen(unsigned int color);
unsigned int get_screen_width(void);
unsigned int get_screen_height(void);

#endif
