#include <drivers/vga.h>

short* vMem = (short*)0xb8000;

void vga::setBackgroundColor(vga::color col){
    for(int i = 0; i < 80*25; i++){
        vMem[i] = (vMem[i] & 0x0FFF) + (col << 12);
    }
}

void vga::putc(uint8_t x, uint8_t y, vga::color col, char c){
    vMem[x+80*y] = (vMem[x+80*y] & 0xF000) + c + (col << 8);    
}

char vga::getc(uint8_t x, uint8_t y){
    return vMem[x+80*y] & 0x00FF;
}

void vga::clearScreen(){
    for(int y = 0; y < 25; y++){
        for(int x = 0; x < 80; x++){
            vMem[x+80*y] = vMem[x+80*y] & 0xF000;
        }
    }
}