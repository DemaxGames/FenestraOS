#include <drivers/irq.h>

#include <drivers/io.h>

#include <fenestra/kernel.h>

void* irqRoutines[16]{0};

int currIrqLife = 0;

extern "C" void irq_handler(idt::InterruptRegs *regs){
    currIrqLife = IRQ_LIFETIME;
    printk(0, 24, "IRQ%d", regs->number);
    void(*handler)(idt::InterruptRegs* regs) = (void(*)(idt::InterruptRegs*))irqRoutines[regs->number];
    if(handler != nullptr) handler(regs);

    port::write(0x20, 0x20);
    return;
}

int irq::SetHandler(int n, void(*handler)(idt::InterruptRegs* regs)){
    if(n < 0 || n > 15) return -1;
    if(handler == nullptr) return -1;

    irqRoutines[n] = (void*)handler;

    return 0;
}