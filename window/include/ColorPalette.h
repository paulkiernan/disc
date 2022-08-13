#ifndef COLORPALETTE_H_INCLUDED
#define COLORPALETTE_H_INCLUDED

#include <FastLED.h>

namespace ColorPalette
{
    enum Color : uint32_t
    {
        DominantWindowColor = CRGB::HotPink,
        BottomWindowAccent  = CRGB::DarkViolet,
        TopWindowAccent     = CRGB::DarkSlateBlue,
        PhoneLightColor     = CRGB::Gold, 
        StopLightGoColor    = CRGB::Green,
        StopLightStopColor  = CRGB::Red,
    };

};

#endif