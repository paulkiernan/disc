#ifndef DISC_H_INCLUDED
#define DISC_H_INCLUDED

#define USE_OCTOWS2811

#include "Addressing.h"
#include "CTeensy4Controller.h"

#include <OctoWS2811.h>
#include <FastLED.h>

class CDisc
{
    public:
        static constexpr uint8_t c_brightness       = 255;
        static constexpr uint8_t c_indicatorPin     = 13;
        static constexpr uint8_t c_indicatorDelayMs = 250;

        static constexpr uint8_t c_numPins = 3;
        static uint8_t c_pinList[c_numPins];

        static constexpr uint8_t c_ledsPerSection = 27;
        static constexpr uint8_t c_sectionsPerStrip = 4;
        static constexpr uint8_t c_bytesPerLED = 4;  // RGBW = one byte per RGB+W

        static constexpr uint32_t c_ledsPerStrip = c_ledsPerSection * c_sectionsPerStrip;
        static constexpr uint8_t  c_kMatrixWidth = c_ledsPerSection;
        static constexpr uint8_t  c_kMatrixHeight = 12;

        //static constexpr size_t c_num_shapes       = 22;

    public: // singleton
        static CDisc& Instance();
        CDisc();
        ~CDisc();

    public:
        void Continue();
        void ShutDown() { m_shutting_down = true; }
        bool ShuttingDown() { return m_shutting_down; }
        static size_t Iteration() { return s_iteration; }
        size_t XY(size_t x, size_t y);
        size_t XYSafe(size_t x, size_t y);

    public: 
        virtual void Show();

    /*
    private:
        CPixelArray* m_geometry      = nullptr;
        CPixelArray* m_show          = nullptr;
    */

    private:
        size_t m_lastIndicator = 0;
        bool   m_indicatorOn   = false;
        bool   m_shutting_down = false;

        OctoWS2811*                             p_octo       = nullptr;
        CTeensy4Controller<BGR, WS2813_800kHz>* p_controller = nullptr;

    private:
        static size_t s_iteration;

        // These buffers need to be large enough for all the pixels.
        // The total number of pixels is "ledsPerStrip * numPins".
        // Each pixel needs 4 bytes, so multiply by 4.  An "int" is
        // 4 bytes, so divide by 4.  The array is created using "int"
        // so the compiler will align it to 32 bit memory.
        //
        // Setup the following drawing spaces:
        //   * CRGB array the main program writes changes to
        //   * OctoWS2811 pointer for syncing LED values to strip
        //   * CTeensy4Controller - FastLED->OctoWS2811 bridge controller
        static DMAMEM int s_displayMemory[c_ledsPerStrip * c_numPins * c_bytesPerLED / 4];
        static int        s_drawingMemory[c_ledsPerStrip * c_numPins * c_bytesPerLED / 4];
        static CRGB       s_ledarray[c_numPins * c_ledsPerStrip];
};

#endif