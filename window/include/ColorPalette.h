#ifndef COLORPALETTE_H_INCLUDED
#define COLORPALETTE_H_INCLUDED

#include <FastLED.h>

namespace ColorPalette
{
    enum Color : uint32_t
    {
        DominantWindow     = CRGB::HotPink,
        BottomWindowAccent = CRGB::DarkViolet,
        TopWindowAccent    = CRGB::DarkSlateBlue,
        PhoneLight         = CRGB::WhiteSmoke,
        StopLightGo        = CRGB::Green,
        StopLightStop      = CRGB::Red,
        Black              = CRGB::Black,
        White              = CRGB::White,
    };

};

#endif
