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
    
    // Jump to C code
    bl main
    
    // Hang if main returns
    b hang

memzero:
    str xzr, [x0], #8
    subs x1, x1, #8
    b.gt memzero
    ret
