#pragma once

#include <stdint.h>
//ACCESS BIT
#define VALID_SEGMENT 0b10000000
#define RING_0 0b00000000
#define RING_1 0b00100000
#define RING_2 0b01000000
#define RING_3 0b01100000
#define CODE_SEGMENT 0b00011000
#define DATA_SEGMENT 0b00010000
//FLAGS
#define GRANULARITY 0b1000
#define PROTECTED_32bSEGMENT 0b0100
#define PROTECTED_16bSEGMENT 0b0000
#define LONG_SEGMENT 0b0010

namespace gdt{
    void flush();
}