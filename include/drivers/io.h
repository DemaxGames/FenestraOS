#pragma once
#include <stdint.h>

namespace port{
    static inline uint8_t read(uint16_t port) {
        uint8_t value;
        __asm__ volatile ( "inb %w1, %b0"
                    : "=a"(value)
                    : "Nd"(port)
                    : "memory");
        return value;
    }

    static inline void write(uint16_t port, uint8_t value)
    {
        __asm__ volatile ( "outb %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
    }
}