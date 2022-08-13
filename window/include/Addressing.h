#ifndef ADDRESSING_H_INCLUDED
#define ADDRESSING_H_INCLUDED

#include <stdint.h>

#include <stddef.h>

#include "Utils.h"

namespace Addressing
{
    static constexpr uint8_t c_num_pins            = 3;
    static constexpr uint8_t c_indicator_pin       = 13;
    static constexpr uint8_t           c_pinList[c_num_pins] = {4, 3, 2};
};

#endif