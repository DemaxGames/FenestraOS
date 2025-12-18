#pragma once

#include <drivers/io.h>

#define PIT_CH0_DATA 0x40
#define PIT_CH1_DATA 0x41
#define PIT_CH2_DATA 0x42
#define PIT_COMMAND 0x43

namespace device{
namespace pit{

    int init();
}
}