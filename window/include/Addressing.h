#ifndef ADDRESSING_H_INCLUDED
#define ADDRESSING_H_INCLUDED

#include <stdint.h>

namespace Addressing
{
    static constexpr uint8_t c_num_pins            = 3;
    static constexpr uint8_t c_indicator_pin       = 13;
    static constexpr uint8_t c_pin_list[c_num_pins] = {4, 3, 2};
};

#endif