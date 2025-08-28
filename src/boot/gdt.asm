GDT_Start:
    Null_Descriptor:
        dd 0x0
        dd 0x0
    Code_Segment_Descriptor:
        dw 0xffff
        dw 0
        db 0
        db 0b10011010
        db 0b11001111
        db 0
    Data_Segment_Descriptor:
        dw 0xffff
        dw 0
        db 0
        db 0b10010010
        db 0b11001111
        db 0
GDT_End:

GDTR:
    dw GDT_End - GDT_Start - 1
    dd GDT_Start