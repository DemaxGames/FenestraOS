#pragma once

#include <stdint.h>
#include <fenestra/kernel.h>
namespace idt
{   
    enum Gate_Type : uint8_t{
    Task_Gate=0x5,
    Interrupt_Gate16b=0x6,
    Trap_Gate16b=0x7,
    Interrupt_Gate32b=0xE,
    Trap_Gate32b=0xF
    };
    enum DPL : uint8_t{
        RING0=0b0,
        RING1=0b00100000,
        RING2=0b01000000,
        RING3=0b01100000
    };
    enum Valid : uint8_t{
        valid=0b10000000,
        not_valid=0b0
    };

    enum type{
        interrupt,
        trap
    };

    void init();
    void setHandler(uint8_t n, void (*foo)(), type gate);

    struct InterruptRegs{
        uint32_t gs, fs, es, ds;
        uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
        uint32_t number;
        uint32_t errorCode;
        uint32_t eip, cs, eflags, useresp, ss;
    } __attribute__ ((packed));

    void isr_handler(InterruptRegs iRegs);

    extern "C" void isr0();
    extern "C" void isr1();
    extern "C" void isr2();
    extern "C" void isr3();
    extern "C" void isr4();
    extern "C" void isr5();
    extern "C" void isr6();
    extern "C" void isr7();
    extern "C" void isr8();
    extern "C" void isr9();
    extern "C" void isr10();
    extern "C" void isr11();
    extern "C" void isr12();
    extern "C" void isr13();
    extern "C" void isr14();
    extern "C" void isr15();
    extern "C" void isr16();
    extern "C" void isr17();
    extern "C" void isr18();
    extern "C" void isr19();
    extern "C" void isr20();
    extern "C" void isr21();
    extern "C" void isr22();
    extern "C" void irq0();
    extern "C" void irq1();
    extern "C" void irq2();
    extern "C" void irq3();
    extern "C" void irq4();
    extern "C" void irq5();
    extern "C" void irq6();
    extern "C" void irq7();
    extern "C" void irq8();
    extern "C" void irq9();
    extern "C" void irq10();
    extern "C" void irq11();
    extern "C" void irq12();
    extern "C" void irq13();
    extern "C" void irq14();
    extern "C" void irq15();
    
} // namespace idt
