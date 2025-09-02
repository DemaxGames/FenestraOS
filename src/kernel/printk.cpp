#include <fenestra/kernel.h>

#define NUM_BUFF_SIZE 30
#define BIN_BUFF_SIZE 64

uint8_t printk_x = 0;
uint8_t printk_y = 0;

void printString(uint8_t *x, uint8_t *y, vga::color col, const char *s){
    for(int i = 0; s[i] != 0; i++){
        if(s[i] == '\n'){
            *x = 0;
            *y++;
            continue;
        }
        else{
            vga::putc(*x, *y, col, s[i]);
        }
        (*x)++;
        if((*x) > 80){
            *x = 0;
            (*y)++;
            if(*y > 25) *y = 0;
        }
    }
    (*x)--;
}

void printInt(uint8_t *x, uint8_t *y, vga::color col, int num){
    char buf[NUM_BUFF_SIZE];
    int ptr = NUM_BUFF_SIZE-1;
    int n = num;
    if(n < 0) n *= -1;

    for(; ptr > 0; ptr--){
        buf[ptr] = (n % 10) + '0';
        n /= 10;
        if(n == 0) break;
    }  
    if(num < 0) buf[--ptr] = '-';

    for(int i = ptr; i < NUM_BUFF_SIZE; i++){
        vga::putc(*x, *y, col, buf[i]);
        (*x)++;
        if(*x > 80){
            *x = 0;
            (*y)++;
            if(*y > 25) *y = 0;
        }
    }
    (*x)--;
}

void printBin(uint8_t *x, uint8_t *y, vga::color col, int num){
    char buf[BIN_BUFF_SIZE];
    int ptr = BIN_BUFF_SIZE-1;
    int n = num;
    if(n < 0) n *= -1;

    for(; ptr > 0; ptr--){
        buf[ptr] = (n % 2) + '0';
        n /= 2;
        if(n == 0) break;
    }  
    if(num < 0) buf[--ptr] = '-';

    for(int i = ptr; i < BIN_BUFF_SIZE; i++){
        vga::putc(*x, *y, col, buf[i]);
        (*x)++;
        if(*x > 80){
            *x = 0;
            (*y)++;
            if(*y > 25) *y = 0;
        }
    }
    (*x)--;
}

int printk(const char *s, ...){
    
    va_list argList;
    int n;

    for(int i = 0; s[i] != 0 ; i++){
        if(argList[i] == '%') n++;
    }
    
    va_start(argList, n);

    for(int ptr = 0; s[ptr] != 0 && ptr < 80*25; ptr++){
        switch(s[ptr]){
            case '%':
                ptr++;
                switch(s[ptr]){
                    case 'd':
                        printInt(&printk_x, &printk_y, vga::color::cyan, va_arg(argList, int));
                        break;
                    case 'i':
                        printInt(&printk_x, &printk_y, vga::color::cyan, va_arg(argList, int));
                        break;
                    case 'b':
                        printBin(&printk_x, &printk_y, vga::color::cyan, va_arg(argList, int));
                        break;
                    case 's':
                        printString(&printk_x, &printk_y, vga::color::light_cyan, va_arg(argList, const char*));
                        break;
                    default:
                        vga::putc(printk_x, printk_y, vga::color::light_cyan, s[ptr]);
                }
                break;
            case '\n':
                    printk_x = 0;
                    printk_y++;
                    continue;
                break;
            default:
                vga::putc(printk_x, printk_y, vga::color::light_cyan, s[ptr]);
        }
        printk_x++;
        if(printk_x > 80){
            printk_x = 0;
            printk_y++;
            if(printk_y > 25) printk_y = 0;
        }
    }
    va_end(argList);
    return 0;
}

int printk(uint8_t x, uint8_t y, const char *s, ...){
    
    va_list argList;
    int n;

    for(int i = 0; s[i] != 0 ; i++){
        if(argList[i] == '%') n++;
    }
    
    va_start(argList, n);

    for(int ptr = 0; s[ptr] != 0 && ptr < 80*25; ptr++){
        switch(s[ptr]){
            case '%':
                ptr++;
                switch(s[ptr]){
                    case 'd':
                        printInt(&x, &y, vga::color::cyan, va_arg(argList, int));
                        break;
                    case 'i':
                        printInt(&x, &y, vga::color::cyan, va_arg(argList, int));
                        break;
                    case 's':
                        printString(&x, &y, vga::color::light_cyan, va_arg(argList, const char*));
                        break;
                    default:
                        vga::putc(x, y, vga::color::light_cyan, s[ptr]);
                }
                break;
            case '\n':
                    x = 0;
                    y++;
                    continue;
                break;
            default:
                vga::putc(x, y, vga::color::light_cyan, s[ptr]);
        }
        x++;
        if(x > 80){
            x = 0;
            y++;
            if(y > 25) y = 0;
        }
    }
    va_end(argList);
    return 0;
}