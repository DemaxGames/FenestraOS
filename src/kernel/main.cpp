extern "C" void main(){
    char* vMem = (char*)0xb8000;
    for(int i = 0; vMem < (char*)(0xb8000 + 80*25*2); i++){
        *vMem = 0xA4;
        vMem++;
        *vMem = i;
        vMem++;
    }

    for(;;);
    return;
}