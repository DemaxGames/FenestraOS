#include <drivers/vga.h>
#include <drivers/io.h>
#include <drivers/gdt.h>
#include <drivers/idt.h>
#include <fenestra/kernel.h>

const char* str = "Some string u know\n";
extern "C" void main(){
    vga::clearScreen();
    vga::setBackgroundColor(vga::color::black);

    const char* osName = "FenestraOS";

    printk("Hello %s v%d.%d.%i\n", osName, 0, 0, 1);

    int a = 50;

    gdt::flush();
    idt::init();

    printk("%h\n%b\n%d\n", 0x55AA, 0x55AA, 0x55AA);

    for(;;);
    return;
}

