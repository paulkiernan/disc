#ifndef COLORPALETTE_H_INCLUDED
#define COLORPALETTE_H_INCLUDED

#include <FastLED.h>

namespace ColorPalette
{
    enum Color : uint32_t
    {
        DominantWindow     = CRGB::White,
        BottomWindowAccent = CRGB::White,
        TopWindowAccent    = CRGB::White,
        PhoneLight         = CRGB::White, 
    };

    constexpr Color s_colors[4] = { 
        DominantWindow,
        BottomWindowAccent,
        TopWindowAccent,
        PhoneLight
    };
};

#endif