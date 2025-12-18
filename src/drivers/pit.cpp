#include <drivers/pit.h>

#include <drivers/idt.h>
#include <drivers/irq.h>
#include <fenestra/kernel.h>

uint64_t ticks;
uint32_t freq = 100;

extern "C" void timerInterrupt(idt::InterruptRegs* regs){
    ticks += 1;
    printk(21, 24, "%d", ticks);
}

int device::pit::init(){
    ticks = 0;
    irq::SetHandler(0, timerInterrupt);

    uint32_t divisor = 1193180 / freq;
    port::write(PIT_COMMAND, 0b00110110);
    port::write(PIT_CH0_DATA, (uint8_t)(divisor & 0xFF));
    port::write(PIT_CH0_DATA, (uint8_t)((divisor >> 8) & 0xFF));
    divisor = 1193180 / 1900;
    port::write(PIT_COMMAND, 0b11110110);
    port::write(PIT_CH0_DATA, (uint8_t)(divisor & 0xFF));
    port::write(PIT_CH0_DATA, (uint8_t)((divisor >> 8) & 0xFF));
    return 0;
}