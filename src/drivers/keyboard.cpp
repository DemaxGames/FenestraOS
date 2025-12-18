#include <drivers/keyboard.h>

#include <fenestra/kernel.h>

#include <drivers/idt.h>
#include <drivers/irq.h>

extern "C" void KeyboardInterrupt(idt::InterruptRegs*){
    uint8_t value = port::read(0x60);
    printk(6, 24, "%X key %X", value & 0x80, value & 0x7F);
}

int device::keyboard::init(){    
    port::write(PORT_KEYBOARD_COMMAND, 0xAA);
    int status = port::read(PORT_KEYBOARD_DATA);
    if(status == 0x55) printk("PS/2 controller test passed...\n");
    else if(status == 0xFC) printk("PS/2 CONTROLLER TEST FAILED!!\n");
    else printk("invalid signal from PS/2 controller: %X\n", status);    
    
    port::write(PORT_KEYBOARD_COMMAND, 0xAD);
    port::write(PORT_KEYBOARD_DATA, 0xF4);

    irq::SetHandler(1, KeyboardInterrupt);
    return 0;
}


int device::keyboard::getScanCode(){
    return port::read(PORT_KEYBOARD_DATA);
}