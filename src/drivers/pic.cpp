#include <drivers/pic.h>

#include <fenestra/kernel.h>
#include <drivers/idt.h>

int device::pic::init(){
    port::write(PIC_MASTER_COMMAND, 0x10 | 0x1);
    port::write(PIC_SLAVE_COMMAND, 0x10 | 0x1);

    port::write(PIC_MASTER_DATA, 0x20);
    port::write(PIC_SLAVE_DATA, 0x28);
    
    port::write(PIC_MASTER_DATA, 1 << 2);
    port::write(PIC_SLAVE_DATA, 2);

    port::write(PIC_MASTER_DATA, 0x01);
    port::write(PIC_SLAVE_DATA, 0x01);
    
    port::write(PIC_MASTER_DATA, 0b11111100);
    port::write(PIC_SLAVE_DATA, 0b11111111);

    printk("both PIC controllers initialization ended succesfully\n");

    return 0;
}