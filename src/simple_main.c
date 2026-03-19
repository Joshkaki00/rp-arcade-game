void main(void) {
    // Use Pi 3 addresses - more compatible
    volatile unsigned int *mailbox_write = (volatile unsigned int*)0x3F00B8A0;
    volatile unsigned int *mailbox_status = (volatile unsigned int*)0x3F00B898;
    
    unsigned int mb[36] __attribute__((aligned(16)));
    
    // Setup framebuffer request
    mb[0] = 35 * 4;
    mb[1] = 0;
    mb[2] = 0x48003; mb[3] = 8; mb[4] = 8; mb[5] = 640; mb[6] = 480;
    mb[7] = 0x48004; mb[8] = 8; mb[9] = 8; mb[10] = 640; mb[11] = 480;
    mb[12] = 0x48009; mb[13] = 8; mb[14] = 8; mb[15] = 0; mb[16] = 0;
    mb[17] = 0x48005; mb[18] = 4; mb[19] = 4; mb[20] = 32;
    mb[21] = 0x48006; mb[22] = 4; mb[23] = 4; mb[24] = 1;
    mb[25] = 0x40001; mb[26] = 8; mb[27] = 8; mb[28] = 4096; mb[29] = 0;
    mb[30] = 0x40008; mb[31] = 4; mb[32] = 4; mb[33] = 0;
    mb[34] = 0;
    
    // Send mailbox message
    unsigned int addr = (unsigned int)((unsigned long)&mb);
    while (*mailbox_status & 0x80000000);
    *mailbox_write = (addr & ~0xF) | 8;
    
    // Get framebuffer
    unsigned int *fb = (unsigned int*)(unsigned long)(mb[28] & 0x3FFFFFFF);
    
    // Fill with red
    for (int i = 0; i < 640*480; i++) fb[i] = 0xFF0000;
    
    while(1);
}
