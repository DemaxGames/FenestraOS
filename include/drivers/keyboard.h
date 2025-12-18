#pragma once

#include <drivers/io.h>

#define PORT_KEYBOARD_DATA 0x60
#define PORT_KEYBOARD_STATUS 0x64
#define PORT_KEYBOARD_COMMAND 0x64


namespace device{
namespace keyboard{

    int init();
    int getScanCode();
}
}