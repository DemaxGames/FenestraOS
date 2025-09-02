extern char printk_x;
extern char printk_y;


extern "C" void _init(){
    printk_x = 0;
    printk_y = 0;
}