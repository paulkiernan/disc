#ifndef DISC_H_INCLUDED
#define DISC_H_INCLUDED

#define USE_OCTOWS2811

#include "Addressing.h"
#include "DrawingFrame.h"
#include "CTeensy4Controller.h"

#include <OctoWS2811.h>

class CDisc
{
    public:
        static constexpr uint8_t c_brightness         = 255;
        static constexpr uint8_t c_indicator_delay_ms = 250;

        static constexpr uint8_t  c_window_height      = 12;
        static constexpr uint8_t  c_leds_per_section   = 27;
        static constexpr uint8_t  c_sections_per_strip = 4;
        static constexpr uint8_t  c_bytes_per_led      = 4;  // RGBW = one byte per RGB+W
        static constexpr uint32_t c_leds_per_strip     = c_leds_per_section * c_sections_per_strip;

    public:
        static CDisc& Instance();  // singleton
        CDisc();
        ~CDisc();

    public:
        void   Continue();
        void   ShutDown()                 { m_shutting_down = true; }
        bool   ShuttingDown()             { return m_shutting_down; }
        static size_t Iteration()         { return s_iteration; }
        size_t XY(size_t x, size_t y);
        size_t XYSafe(size_t x, size_t y);

    public: 
        virtual void Show();

    private:
        CDrawingFrame* m_frame = nullptr;

    private:
        size_t m_last_indicator = 0;
        bool   m_indicator_on   = false;
        bool   m_shutting_down  = false;

        OctoWS2811*                             p_octo       = nullptr;
        CTeensy4Controller<BGR, WS2813_800kHz>* p_controller = nullptr;

    private:
        static size_t s_iteration;

        // These buffers need to be large enough for all the pixels.
        // The total number of pixels is "leds_per_strip * numPins".
        // Each pixel needs 4 bytes, so multiply by 4.  An "int" is
        // 4 bytes, so divide by 4.  The array is created using "int"
        // so the compiler will align it to 32 bit memory.
        //
        // Setup the following drawing spaces:
        //   * CRGB array the main program writes changes to
        //   * OctoWS2811 pointer for syncing LED values to strip
        //   * CTeensy4Controller - FastLED->OctoWS2811 bridge controller
        static DMAMEM int s_display_memory[c_leds_per_strip * Addressing::c_num_pins * c_bytes_per_led / 4];
        static int        s_drawing_memory[c_leds_per_strip * Addressing::c_num_pins * c_bytes_per_led / 4];
        static CRGB       s_leds[Addressing::c_num_pins * c_leds_per_strip];
};

#endif