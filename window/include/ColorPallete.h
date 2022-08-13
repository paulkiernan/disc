#ifndef COLORPALLETE_H_INCLUDED
#define COLORPALLETE_H_INCLUDED

#include "FastLED.h"

namespace ColorPallete
{
    enum Color : uint32_t
    {
        Mint        = 0x00B43C,
        Purple      = 0x760096,
        Blue        = 0x0A00B4,
        DarkPink    = 0xC30032,
        Qty         = 4,
    };

    constexpr Color s_colors[Qty] = { Mint, Purple, Blue, DarkPink };
};

#endif