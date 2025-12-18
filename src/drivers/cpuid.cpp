#include "drivers/cpu.h"

extern "C" cpu::cpuid_data asmGetcpuid(uint32_t);

struct {
    char vendorID[13];
    uint32_t maxInputValue;
    uint32_t featuresA, featuresB;
} internalData;

namespace cpu{
    const char* vendorID;
    const uint32_t& maxInputValue = internalData.maxInputValue;
    const uint32_t& featuresA = internalData.featuresA, featuresB = internalData.featuresB;
}

cpu::cpuid_data cpu::cpuid(uint32_t eax){
    return asmGetcpuid(eax);
}

void cpu::identify(){
    cpu::cpuid_data data{0};
    data = asmGetcpuid(0);
    internalData.maxInputValue = data.eax;
    ((uint32_t*)internalData.vendorID)[0] = data.ebx;
    ((uint32_t*)internalData.vendorID)[1] = data.ecx;
    ((uint32_t*)internalData.vendorID)[2] = data.edx;
    vendorID = internalData.vendorID;

    data = asmGetcpuid(1);
    internalData.featuresA = data.ecx;
    internalData.featuresB = data.edx;

}

