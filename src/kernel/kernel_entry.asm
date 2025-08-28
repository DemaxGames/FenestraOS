[bits 32]
section .entry
[extern main]
[global start_kernel]
start_kernel:
    call main