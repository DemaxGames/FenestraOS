[BITS 32]

global asmGetcpuid
asmGetcpuid:
    push ebp
    mov ebp, esp

    mov eax, DWORD [ebp+12]
    cpuid
    mov esi, eax

    mov     eax, DWORD [ebp+8]
    mov     DWORD [eax], esi
    mov     eax, DWORD [ebp+8]
    mov     DWORD [eax+4], ebx
    mov     eax, DWORD [ebp+8]
    mov     DWORD [eax+8], ecx
    mov     eax, DWORD [ebp+8]
    mov     DWORD [eax+12], edx
    nop
    mov     eax, [ebp+8]
    pop     ebp
    ret     4
