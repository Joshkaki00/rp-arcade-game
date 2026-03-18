#ifndef MAILBOX_H
#define MAILBOX_H

int mailbox_call(unsigned int channel);
unsigned int* get_mailbox_buffer(void);

#endif
