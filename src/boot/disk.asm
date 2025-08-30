load_kernel_from_disk:  ;AX - BIOS drive number, BX - location to load, CX - count of sectors to load < 63
    mov [drive_number], ax
    mov [kernel_location_var], bx
    mov [kernel_size_var], cx

    mov bx, msg
    call print

    mov dl, [drive_number]
    mov ah, 2
    mov al, 63
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, [kernel_location_var]
    int 0x13

    mov ax, [kernel_size_loaded]
    add ax, 63
    mov [kernel_size_loaded], ax
    mov ax, [kernel_location_var]
    add ax, 0x7e00 ;63 * 512 in hex
    mov [kernel_location_var], ax
    mov ax, [cylinder]
    inc ax
    mov [cylinder], ax

    mov ax, [kernel_size_loaded]
    cmp ax, [kernel_size_var]
    jb load_kernel_from_disk_loop
    jmp load_kernel_from_disk_exit

load_kernel_from_disk_loop:
    mov bx, msg
    call print

    mov dl, [drive_number]
    mov ah, 2
    mov al, 63
    mov ch, [cylinder]
    mov cl, 1
    mov dh, 0
    mov bx, [kernel_location_var]
    int 0x13

    mov ax, [kernel_size_loaded]
    add ax, 63
    mov [kernel_size_loaded], ax
    mov ax, [kernel_location_var]
    add ax, 0x7e00 ;63 * 512 in hex
    mov [kernel_location_var], ax
    mov ax, [cylinder]
    inc ax
    mov [cylinder], ax

    mov ax, [kernel_size_loaded]
    cmp ax, [kernel_size_var]
    jb load_kernel_from_disk_loop
    jmp load_kernel_from_disk_exit


load_kernel_from_disk_exit:
    ret

drive_number: dw 0
kernel_size_var: dw 0
kernel_size_loaded: dw 0
kernel_location_var: dw 0
cylinder: dw 0