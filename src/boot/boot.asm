[bits 16]
[org 0x7c00]
CODE_SEG equ Code_Segment_Descriptor - GDT_Start
DATA_SEG equ Data_Segment_Descriptor - GDT_Start
KERNEL_LOCATION equ 0x7e00
KERNEL_SIZE equ 5 ;kernel size in sectors, must be < 128
mov [diskNum], dl

xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov bp, 0x7c00
mov sp, bp

mov ah, 0x00
mov al, 0x03
int 0x10


loading_kernel:
    mov ax, [diskNum]
    mov bx, KERNEL_LOCATION
    mov cx, KERNEL_SIZE
    call load_kernel_from_disk


enabling_a20:
    mov bx, msg1
    call print
    in al, 0x92
    or al, 2
    out 0x92, al

enabling_gdt:
    cli
    lgdt [GDTR]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:start_protected_mode



%include "print.asm"

msg: db "Loading from disk...", 10, 13, 0
msg1: db "Enabling A20 Line...", 10, 13, 0
diskNum: db 0


%include "disk.asm"
%include "gdt.asm"
%include "protected.asm"
times 510-($-$$) db 0
db 0x55, 0xaa