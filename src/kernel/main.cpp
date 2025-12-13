#include <drivers/vga.h>
#include <drivers/io.h>
#include <drivers/irq.h>
#include <drivers/gdt.h>
#include <drivers/idt.h>
#include <drivers/cpu.h>
#include <drivers/keyboard.h>
#include <drivers/pic.h>
#include <drivers/pit.h>
#include <fenestra/kernel.h>

extern "C" void main(){
    vga::clearScreen();
    vga::setBackgroundColor(vga::color::black);

    const char* osName = "FenestraOS";

    printk("Hello %s v%d.%d.%i\n", osName, 0, 0, 1);

    gdt::flush();

    device::pic::init();
    idt::init();
    device::pit::init();
    device::keyboard::init();

    cpu::identify();
    printk("max: %d\n", cpu::maxInputValue);
    printk("vendorID: %s\n", cpu::vendorID);
    printk("features: %b , %b\n", cpu::featuresA, cpu::featuresB);

    uint32_t Div = 1193180 / 9000;
    port::write(0x43, 0xb6);
 	port::write(0x42, (uint8_t) (Div) );
 	port::write(0x42, (uint8_t) (Div >> 8));

    uint8_t tmp = port::read(0x61);
  	if (tmp != (tmp | 3)) {
 		port::write(0x61, tmp | 3);
    }
    asm volatile ("sti");

    
    for(int i = 0;;i++){
        printk(50, 24, "%d", i);
        asm volatile ("hlt");
    }
    return;
}

