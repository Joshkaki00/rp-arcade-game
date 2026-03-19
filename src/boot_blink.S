.section ".text.boot"

.global _start

_start:
    // Get CPU ID
    mrs x0, mpidr_el1
    and x0, x0, #3
    cbz x0, master
    
hang:
    wfe
    b hang

master:
    // Set stack pointer
    ldr x0, =_start
    mov sp, x0
    
    // Clear BSS
    ldr x0, =__bss_start
    ldr x1, =__bss_end
    sub x1, x1, x0
    bl memzero
    
    // Instead of jumping to main, just blink using a loop
    // This proves the kernel is executing
blink_loop:
    // Long delay - use smaller immediate values
    mov x0, #0x1000
    lsl x0, x0, #12    // Multiply by 4096
delay1:
    sub x0, x0, #1
    cbnz x0, delay1
    
    // Another long delay
    mov x0, #0x1000
    lsl x0, x0, #12
delay2:
    sub x0, x0, #1
    cbnz x0, delay2
    
    b blink_loop

memzero:
    str xzr, [x0], #8
    subs x1, x1, #8
    b.gt memzero
    ret
