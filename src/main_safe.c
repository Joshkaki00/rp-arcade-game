#include "framebuffer.h"
#include "mailbox.h"

void main(void) {
    unsigned int width = 1280;
    unsigned int height = 720;
    unsigned int pitch;
    unsigned int *framebuffer;
    
    // Try to initialize framebuffer
    unsigned int *mb = get_mailbox_buffer();
    
    mb[0] = 35 * 4;
    mb[1] = 0;
    
    mb[2] = 0x48003;  // Set physical width/height
    mb[3] = 8;
    mb[4] = 8;
    mb[5] = width;
    mb[6] = height;
    
    mb[7] = 0x48004;  // Set virtual width/height
    mb[8] = 8;
    mb[9] = 8;
    mb[10] = width;
    mb[11] = height;
    
    mb[12] = 0x48009; // Set virtual offset
    mb[13] = 8;
    mb[14] = 8;
    mb[15] = 0;
    mb[16] = 0;
    
    mb[17] = 0x48005; // Set depth
    mb[18] = 4;
    mb[19] = 4;
    mb[20] = 32;
    
    mb[21] = 0x48006; // Set pixel order
    mb[22] = 4;
    mb[23] = 4;
    mb[24] = 1;
    
    mb[25] = 0x40001; // Allocate buffer
    mb[26] = 8;
    mb[27] = 8;
    mb[28] = 4096;
    mb[29] = 0;
    
    mb[30] = 0x40008; // Get pitch
    mb[31] = 4;
    mb[32] = 4;
    mb[33] = 0;
    
    mb[34] = 0;
    
    // Try mailbox call
    if (!mailbox_call(8)) {
        // Mailbox failed - show error pattern using CPU delays
        while (1) {
            // Fast blink pattern = mailbox error
            volatile int i;
            for (i = 0; i < 1000000; i++);
        }
    }
    
    // Mailbox succeeded! Get framebuffer
    framebuffer = (unsigned int*)(unsigned long)(mb[28] & 0x3FFFFFFF);
    pitch = mb[33];
    
    // Try to write to framebuffer - fill with color bands
    for (int y = 0; y < height; y++) {
        unsigned int color;
        
        // Create 7 color bands
        if (y < height / 7) color = 0xFF0000;       // Red
        else if (y < 2 * height / 7) color = 0x00FF00;  // Green
        else if (y < 3 * height / 7) color = 0x0000FF;  // Blue
        else if (y < 4 * height / 7) color = 0xFFFF00;  // Yellow
        else if (y < 5 * height / 7) color = 0x00FFFF;  // Cyan
        else if (y < 6 * height / 7) color = 0xFF00FF;  // Magenta
        else color = 0xFFFFFF;                          // White
        
        for (int x = 0; x < width; x++) {
            framebuffer[y * (pitch / 4) + x] = color;
        }
    }
    
    // Success! Slow blink pattern
    while (1) {
        volatile int i;
        for (i = 0; i < 10000000; i++);
    }
}
