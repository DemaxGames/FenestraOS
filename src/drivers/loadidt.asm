[BITS 32]

extern irq_handler
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

%macro IRQ 1
    global irq%1
    irq%1:
        cli
        push long %1
        jmp irq_common_stub
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

IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15

isr_common_stub:
    pushad
    push dword ds
    push dword es
    push dword fs
    push dword gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp

    push eax
    mov eax, isr_handler
    call eax

    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8
    iret


irq_common_stub:
    pushad
    push dword ds
    push dword es
    push dword fs
    push dword gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp

    push eax
    mov eax, irq_handler
    call eax

    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 0x04
    iret