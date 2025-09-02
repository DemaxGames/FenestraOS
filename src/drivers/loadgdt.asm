[BITS 32]

global loadgdtr
loadgdtr:
    mov eax, [esp+4]
    lgdt [eax]

    mov eax, 0x10
    mov ds, ax
    mov fs, ax
    mov es, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.reloadS
.reloadS:
    ret