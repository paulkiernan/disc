#ifndef CTEENSY4CONTROLLER_H_INCLUDED
#define CTEENSY4CONTROLLER_H_INCLUDED

#include <OctoWS2811.h>
#include <FastLED.h>

template <EOrder RGB_ORDER = RGB,
          uint8_t CHIP = WS2811_800kHz>
class CTeensy4Controller : public CPixelLEDController<RGB_ORDER, 8, 0xFF>
{
    OctoWS2811 *p_octo;

public:
    CTeensy4Controller(OctoWS2811 *_p_octo)
        : p_octo(_p_octo){};

    virtual void init() {}
    virtual void showPixels(PixelController<RGB_ORDER, 8, 0xFF> &pixels)
    {

        uint32_t i = 0;
        while (pixels.has(1))
        {
            uint8_t r = pixels.loadAndScale0();
            uint8_t g = pixels.loadAndScale1();
            uint8_t b = pixels.loadAndScale2();
            p_octo->setPixel(i++, r, g, b);
            pixels.stepDithering();
            pixels.advanceData();
        }

        p_octo->show();
    }
};

#endif