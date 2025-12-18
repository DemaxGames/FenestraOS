ENTRY(start_kernel)

SECTIONS {
    /* Where the kernel starts */
    . = 0x7e00;

    /* Make sure the entry point is the very first thing that is placed in the binary */
    .entry : { *(.entry) }
    .text : { *(.text) }

    .rodata : { *(.rodata) }
    .data : { *(.data) }

    .bss : {
        *(COMMON)
        *(.bss)
    }
}