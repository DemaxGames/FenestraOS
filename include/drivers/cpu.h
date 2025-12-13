#pragma once
#include <stdint.h>
#include <drivers/feature.h>

namespace cpu{

extern const char* vendorID;
extern const uint32_t& maxInputValue; 
extern const uint32_t& featuresA, featuresB;

typedef struct {
    uint32_t eax, ebx, ecx, edx;
} cpuid_data;

void identify();
cpuid_data cpuid(uint32_t eax);
}