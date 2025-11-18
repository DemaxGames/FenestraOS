#include <drivers/idt.h>

#define INTERRUPTS_COUNT 22

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

struct __attribute__((packed)) IDTR{
    uint16_t size;
    uint32_t offset;
};

struct __attribute__((packed)) Entry{
    uint16_t offset_low;
    uint16_t segment;
    uint8_t reserved;
    uint8_t flags;
    uint16_t offset_high;
};

Entry IDT[INTERRUPTS_COUNT];
IDTR idtr;

extern "C" void loadidtr(IDTR*);

void fillEntry(Entry* entry, uint32_t offset,
                uint16_t segment, uint8_t flags){
    entry->offset_low = offset & 0xFFFF;
    entry->segment = segment;
    entry->reserved = 0;
    entry->flags = flags;
    entry->offset_high = (offset & 0xFFFF0000) >> 16;
}

void idt::init(){
    for(int i = 0; i < INTERRUPTS_COUNT; i++){
        fillEntry(&IDT[i], 0, 0x08, not_valid | DPL::RING0 | Gate_Type::Interrupt_Gate32b);
    }

    idt::setHandler(0, isr0, idt::type::interrupt);
    idt::setHandler(1, isr1, idt::type::interrupt);
    idt::setHandler(2, isr2, idt::type::interrupt);
    idt::setHandler(3, isr3, idt::type::interrupt);
    idt::setHandler(4, isr4, idt::type::interrupt);
    idt::setHandler(5, isr5, idt::type::interrupt);
    idt::setHandler(6, isr6, idt::type::interrupt);
    idt::setHandler(7, isr7, idt::type::interrupt);
    idt::setHandler(8, isr8, idt::type::interrupt);
    idt::setHandler(9, isr9, idt::type::interrupt);
    idt::setHandler(10, isr10, idt::type::interrupt);
    idt::setHandler(11, isr11, idt::type::interrupt);
    idt::setHandler(12, isr12, idt::type::interrupt);
    idt::setHandler(13, isr13, idt::type::interrupt);
    idt::setHandler(14, isr14, idt::type::interrupt);
    idt::setHandler(15, isr15, idt::type::interrupt);
    idt::setHandler(16, isr16, idt::type::interrupt);
    idt::setHandler(17, isr17, idt::type::interrupt);
    idt::setHandler(18, isr18, idt::type::interrupt);
    idt::setHandler(19, isr19, idt::type::interrupt);
    idt::setHandler(20, isr20, idt::type::interrupt);
    idt::setHandler(21, isr21, idt::type::interrupt);

    idtr.size = sizeof(Entry) * INTERRUPTS_COUNT;
    idtr.offset = (uint32_t)IDT;

    loadidtr(&idtr);
    printk("IDT Loaded succesfully at adress %h\n", (uint32_t)&idtr);
}

void idt::setHandler(uint8_t n, void (*foo)(), type gate){
    if(gate == idt::type::interrupt){
        fillEntry(&IDT[n], (uint32_t)foo, 0x08, valid | DPL::RING0 | Gate_Type::Interrupt_Gate32b);
    }
    if(gate == idt::type::trap){
        fillEntry(&IDT[n], (uint32_t)foo, 0x08, valid | DPL::RING0 | Gate_Type::Trap_Gate32b);
    }
}

const char *exceptions[]{
    "Divide Error",
    "Debug Exception",
    "NMI Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode (Undefined Opcode)",
    "Device Not Available (No Math Coprocessor)",
    "Double Fault",
    "Coprocessor Segment Overrun (reserved)",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection",
    "Page Fault",
    "Intel reserved. Do not use.",
    "x87 FPU Floating-Point Error (Math Fault)",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception"
};

extern "C" void isr_handler(idt::InterruptRegs *regs){
    if(regs->number < 22){
        printk("Exception: %s\n", exceptions[regs->number]);
    }
}