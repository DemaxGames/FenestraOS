load_kernel_from_disk:  ;AX - BIOS drive number, BX - location to load, CX - count of sectors to load < 72
    mov dl, al
    mov ah, 2
    mov al, cl
    mov ch, 0
    mov cl, 2
    mov dh, 0
    int 0x13
    ret