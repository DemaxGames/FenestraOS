#pragma once
#include <stdint.h>

namespace io{
    uint8_t inline in(uint8_t port){
        uint8_t value;
        asm volatile("inb %b0, %b1" : "=a"(value) :  "d"(port));
        return value;
    }

    void inline out(uint8_t port, uint8_t value){
        asm volatile("outb %b0, %b1" : : "d"(port), "a"(value));
    }
}