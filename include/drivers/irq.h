#pragma once

#include <drivers/idt.h>

#define IRQ_LIFETIME 1000
namespace irq{

int SetHandler(int n, void(*handler)(idt::InterruptRegs* regs));
int Display();
}