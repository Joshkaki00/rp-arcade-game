#include "framebuffer.h"
#include "mailbox.h"

static unsigned int width = 1280;
static unsigned int height = 720;
static unsigned int pitch;
static unsigned int *framebuffer;

int framebuffer_init(void) {
    unsigned int *mb = get_mailbox_buffer();
    
    mb[0] = 35 * 4;
    mb[1] = 0;
    
    mb[2] = 0x48003;
    mb[3] = 8;
    mb[4] = 8;
    mb[5] = width;
    mb[6] = height;
    
    mb[7] = 0x48004;
    mb[8] = 8;
    mb[9] = 8;
    mb[10] = width;
    mb[11] = height;
    
    mb[12] = 0x48009;
    mb[13] = 8;
    mb[14] = 8;
    mb[15] = 0;
    mb[16] = 0;
    
    mb[17] = 0x48005;
    mb[18] = 4;
    mb[19] = 4;
    mb[20] = 32;
    
    mb[21] = 0x48006;
    mb[22] = 4;
    mb[23] = 4;
    mb[24] = 1;
    
    mb[25] = 0x40001;
    mb[26] = 8;
    mb[27] = 8;
    mb[28] = 4096;
    mb[29] = 0;
    
    mb[30] = 0x40008;
    mb[31] = 4;
    mb[32] = 4;
    mb[33] = 0;
    
    mb[34] = 0;
    
    if (!mailbox_call(8))
        return 0;
    
    framebuffer = (unsigned int*)(unsigned long)(mb[28] & 0x3FFFFFFF);
    pitch = mb[33];
    
    return 1;
}

void draw_pixel(int x, int y, unsigned int color) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    
    framebuffer[y * (pitch / 4) + x] = color;
}

void draw_rect(int x, int y, int w, int h, unsigned int color) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            draw_pixel(x + j, y + i, color);
        }
    }
}

void clear_screen(unsigned int color) {
    draw_rect(0, 0, width, height, color);
}

unsigned int get_screen_width(void) { return width; }
unsigned int get_screen_height(void) { return height; }
