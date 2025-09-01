[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp
    
    jmp KERNEL_LOCATION