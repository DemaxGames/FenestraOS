#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <drivers/vga.h>

int printk(const char *s, ...);
int printk(uint8_t x, uint8_t y, const char *s, ...);