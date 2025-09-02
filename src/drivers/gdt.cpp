#include <drivers/gdt.h>
#include <fenestra/kernel.h>

#define SEGMENT_COUNT 5


struct __attribute__((packed)) GDTR{
    uint16_t size;
    uint32_t offset;
};

extern "C" void loadgdtr(GDTR*);

GDTR gdtr;

struct __attribute__((packed)) Entry{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base;
    uint8_t access_byte;
    uint8_t flags_limit;
    uint8_t base_high;
};

Entry GDT[5];

void fillEntry(Entry* entry, uint32_t base, uint32_t limit,
                uint8_t access, uint8_t flags){
    entry->limit_low = limit & 0xFFFF;
    entry->base_low = base & 0xFFFF;
    entry->base = (base & 0xFF0000) >> 16;
    entry->access_byte = access + 0b00000010;
    entry->flags_limit = (limit & 0xF0000) >> 16;
    entry->flags_limit = entry->flags_limit + ((flags & 0xF) << 4);
    entry->base_high = (base & 0xFF000000) >> 24;
    return;
}

void gdt::flush(){
    fillEntry(&GDT[0], 0, 0, 0, 0);
    fillEntry(&GDT[1], 0, 0xFFFFF, VALID_SEGMENT | RING_0 | CODE_SEGMENT, GRANULARITY | PROTECTED_32bSEGMENT);
    fillEntry(&GDT[2], 0, 0xFFFFF, VALID_SEGMENT | RING_0 | DATA_SEGMENT, GRANULARITY | PROTECTED_32bSEGMENT);
    fillEntry(&GDT[3], 0, 0xFFFFF, VALID_SEGMENT | RING_3 | CODE_SEGMENT, GRANULARITY | PROTECTED_32bSEGMENT);
    fillEntry(&GDT[4], 0, 0xFFFFF, VALID_SEGMENT | RING_3 | DATA_SEGMENT, GRANULARITY | PROTECTED_32bSEGMENT);

    int* ptr = (int*)(void*)&GDT[1];


    gdtr.size = sizeof(Entry) * SEGMENT_COUNT;
    gdtr.offset = (uint32_t)GDT;

    loadgdtr(&gdtr);

    printk("GDT Loaded succesfully at adress %d\n", (uint32_t)&gdtr);
}