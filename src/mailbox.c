#include "mailbox.h"

// Pi 4 addresses
#define MAILBOX_BASE_PI4    0xFE00B880

// Pi 5 addresses - try legacy compatibility mode first
#define MAILBOX_BASE_PI5    0x107d508880ULL

// Try both addresses at runtime
static unsigned long long mailbox_base = MAILBOX_BASE_PI4;

#define MAIL_READ       ((volatile unsigned int*)(mailbox_base + 0x00))
#define MAIL_STATUS     ((volatile unsigned int*)(mailbox_base + 0x18))
#define MAIL_WRITE      ((volatile unsigned int*)(mailbox_base + 0x20))

#define MAIL_EMPTY      0x40000000
#define MAIL_FULL       0x80000000

static unsigned int mailbox_buffer[256] __attribute__((aligned(16)));

// Try to detect which mailbox address works
static void detect_mailbox_base(void) {
    // For Pi 5, the mailbox should still be accessible via the VideoCore
    // Try Pi 4 address first (legacy compatibility)
    mailbox_base = MAILBOX_BASE_PI4;
    
    // TODO: Could add detection logic here if needed
    // For now, Pi 4 address should work via firmware compatibility layer
}

int mailbox_call(unsigned int channel) {
    detect_mailbox_base();
    
    unsigned int addr = (unsigned int)((unsigned long)&mailbox_buffer);
    
    while (*MAIL_STATUS & MAIL_FULL);
    
    *MAIL_WRITE = (addr & ~0xF) | (channel & 0xF);
    
    while (1) {
        while (*MAIL_STATUS & MAIL_EMPTY);
        
        if (*MAIL_READ == ((addr & ~0xF) | (channel & 0xF)))
            return mailbox_buffer[1] == 0x80000000;
    }
    
    return 0;
}

unsigned int* get_mailbox_buffer(void) {
    return mailbox_buffer;
}
