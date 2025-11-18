[BITS 32]

extern isr_handler
global loadidtr
loadidtr:
    mov eax, [esp+4]
    lidt [eax]

    ret

%macro ISR_NOERRCODE 1
    global isr%1
    isr%1:
        cli
        push long 0
        push long %1
        jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
    global isr%1
    isr%1:
        cli
        push long %1
        jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE   17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_ERRCODE   21

isr_common_stub:
    pusha
    mov eax, ds
    push eax
    mov eax, cr2
    push eax

    mov eax, 0x10
    mov ds, ax
    mov fs, ax
    mov es, ax
    mov gs, ax
    mov ss, ax

    push esp
    call isr_handler

    add esp, 8
    pop ebx
    mov eax, ebx
    mov ds, ax
    mov fs, ax
    mov es, ax
    mov gs, ax
    mov ss, ax

    popa
    add esp, 8
    sti
    iret
