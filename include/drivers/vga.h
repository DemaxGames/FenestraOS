#pragma once

#include <stdint.h>

namespace vga{
    enum mode{
        Text16c_80x25
    };
    enum color : uint8_t{
        black,
        blue,
        green,
        cyan,
        red,
        purple,
        brown,
        gray,
        dark_gray,
        light_blue,
        light_green,
        light_cyan,
        light_red,
        light_purple,
        yellow,
        white
    };
    void clearScreen();
    void setBackgroundColor(vga::color col);
    void putc(uint8_t x, uint8_t y, vga::color col, char c);
    char getc(uint8_t x, uint8_t y);
};