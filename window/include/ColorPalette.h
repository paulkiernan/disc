#ifndef COLORPALETTE_H_INCLUDED
#define COLORPALETTE_H_INCLUDED

#include <FastLED.h>

namespace ColorPalette
{
    enum Color : uint32_t
    {
        DominantWindowColor = CRGB::HotPink,
        BottomWindowAccent  = CRGB::White,
        TopWindowAccent     = CRGB::White,
        PhoneLight          = CRGB::White, 
    };

    constexpr Color s_colors[4] = { 
        DominantWindowColor,
        BottomWindowAccent,
        TopWindowAccent,
        PhoneLight
    };
};

#endif