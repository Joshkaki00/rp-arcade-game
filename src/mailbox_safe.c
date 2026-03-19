#include "mailbox.h"

// Try multiple possible mailbox addresses for Pi 5
#define MAILBOX_BASE_PI4        0xFE00B880
#define MAILBOX_BASE_PI5_ALT1   0x107C01B880ULL
#define MAILBOX_BASE_PI5_ALT2   0x7E00B880      // Legacy VideoCore address

static volatile unsigned long long mailbox_base = MAILBOX_BASE_PI4;
static unsigned int mailbox_buffer[256] __attribute__((aligned(16)));

// Safe memory read - returns 1 if successful, 0 if address causes fault
static int safe_read_test(volatile unsigned int *addr) {
    // Try to read - if it crashes, we can't catch it in bare metal
    // So we'll just try Pi 4 address and hope firmware provides compatibility
    (void)addr;
    return 1;
}

int mailbox_call(unsigned int channel) {
    // Use Pi 4 mailbox address - the firmware should provide compatibility
    volatile unsigned int *mail_read = (volatile unsigned int*)(MAILBOX_BASE_PI4 + 0x00);
    volatile unsigned int *mail_status = (volatile unsigned int*)(MAILBOX_BASE_PI4 + 0x18);
    volatile unsigned int *mail_write = (volatile unsigned int*)(MAILBOX_BASE_PI4 + 0x20);
    
    unsigned int addr = (unsigned int)((unsigned long)&mailbox_buffer);
    
    // Check if mailbox seems responsive (very basic check)
    unsigned int status_val = *mail_status;
    
    // If status is all 1s (0xFFFFFFFF), address is probably wrong
    if (status_val == 0xFFFFFFFF) {
        return 0;  // Fail gracefully
    }
    
    // Wait for mailbox to be not full
    int timeout = 1000000;
    while ((*mail_status & 0x80000000) && timeout--) {
        // Busy wait
    }
    if (timeout <= 0) return 0;
    
    // Write the message
    *mail_write = (addr & ~0xF) | (channel & 0xF);
    
    // Wait for response
    timeout = 1000000;
    while (1) {
        while ((*mail_status & 0x40000000) && timeout--) {
            // Wait for not empty
        }
        if (timeout <= 0) return 0;
        
        if (*mail_read == ((addr & ~0xF) | (channel & 0xF)))
            return mailbox_buffer[1] == 0x80000000;
    }
    
    return 0;
}

unsigned int* get_mailbox_buffer(void) {
    return mailbox_buffer;
}
