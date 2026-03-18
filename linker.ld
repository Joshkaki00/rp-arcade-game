ENTRY(_start)

SECTIONS
{
    . = 0x80000;
    
    .text : {
        KEEP(*(.text.boot))
        *(.text)
    }
    
    .rodata : {
        *(.rodata)
    }
    
    .data : {
        *(.data)
    }
    
    .bss : {
        __bss_start = .;
        *(.bss)
        __bss_end = .;
    }
    
    . = ALIGN(0x8);
    . = . + 0x4000;
    stack_top = .;
}
