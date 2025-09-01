[bits 32]
section .entry
[extern main]
[extern _init]
[global start_kernel]
start_kernel:
    call _init
    call main