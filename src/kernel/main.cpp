#include <drivers/vga.h>
#include <drivers/io.h>
#include <fenestra/kernel.h>

const char* str = "Some string u know\n";
extern "C" void main(){
    vga::clearScreen();
    vga::setBackgroundColor(vga::color::black);

    const char* osName = "FenestraOS";

    printk("Hello %s v%d.%d.%i\n", osName, 0, 0, 1);

    printk(50, 24, "Time %d:%d:%d", 21, 16, 50);

    printk("%b", 0x55AA);

    for(;;);
    return;
}

