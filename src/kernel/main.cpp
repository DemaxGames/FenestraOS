extern "C" void PrintMemToScreen(char* mem){
    char* vMem = (char*)0xb8000;
    for(int i = 0; vMem < (char*)(0xb8000 + 80*25*2); i++){
        *vMem = *mem;
        vMem++;
        mem++;
        *vMem = 0x0F;
        vMem++;
    }
}
const char* str = "Some string u know\n";
extern "C" void main(){
    char* start = (char*)(0x7e00 + 0x7000);
    for(int i = 0; i < 1200; i++){
        PrintMemToScreen(start);
        start += 80 * 4;
        for(int j = 0; j < 5000000; j++);
    }
    

    for(;;);
    return;
}

