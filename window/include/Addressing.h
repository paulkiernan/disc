#ifndef ADDRESSING_H_INCLUDED
#define ADDRESSING_H_INCLUDED

#include <stdint.h>

namespace Addressing
{
    static constexpr uint8_t c_num_pins             = 3;
    static constexpr uint8_t c_indicator_pin        = 13;
    static constexpr uint8_t c_pin_list[c_num_pins] = {7, 14, 2};
};

#endif
