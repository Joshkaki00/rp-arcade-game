#include "mailbox.h"

#define MAILBOX_BASE    0xFE00B880
#define MAIL_READ       ((volatile unsigned int*)(MAILBOX_BASE + 0x00))
#define MAIL_STATUS     ((volatile unsigned int*)(MAILBOX_BASE + 0x18))
#define MAIL_WRITE      ((volatile unsigned int*)(MAILBOX_BASE + 0x20))

#define MAIL_EMPTY      0x40000000
#define MAIL_FULL       0x80000000

static unsigned int mailbox_buffer[256] __attribute__((aligned(16)));

int mailbox_call(unsigned int channel) {
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
