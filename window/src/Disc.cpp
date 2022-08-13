#include "Disc.h"
#include "Logging.h"
#include "Addressing.h"
#include "Arduino.h"
#include "FreeRam.h"
#include "DrawingFrame.h"
#include "Geometry.h"
#include "PayphoneLight.h"
#include "TrafficLight.h"

size_t     CDisc::s_iteration = 0;
DMAMEM int CDisc::s_display_memory[c_leds_per_strip * Addressing::c_num_pins * c_bytes_per_led / 4];
int        CDisc::s_drawing_memory[c_leds_per_strip * Addressing::c_num_pins * c_bytes_per_led / 4];
CRGB       CDisc::s_leds[Addressing::c_num_pins * c_leds_per_strip];

CDisc& CDisc::Instance()
{
    static CDisc disc;
    return disc;
}

CDisc::CDisc()
{
    Log.infoln("CDisc::CDisc: Initializing Disc");
    pinMode(Addressing::c_indicator_pin, OUTPUT);

    // Setup OctoWS2811 and FastLED
    p_octo = new OctoWS2811(
        c_leds_per_strip,
        s_display_memory,
        s_drawing_memory,
        WS2811_RGB | WS2813_800kHz,
        Addressing::c_num_pins,
        Addressing::c_pin_list
    );
    p_octo->begin();
    p_controller = new CTeensy4Controller<BGR, WS2813_800kHz>(p_octo);
    FastLED.setBrightness(c_brightness);
    FastLED.addLeds(
        p_controller,
        s_leds,
        Addressing::c_num_pins * c_leds_per_strip
    )
    .setCorrection(TypicalPixelString)
    .setDither(c_brightness < 255);
    Log.noticeln("OCTOWS2811 and FastLED Initialized");

    // Setup the scene and objects in them
    m_frame = new CDrawingFrame(
        c_leds_per_section, // width
        c_window_height,   // height
        s_leds        // leds
    );
    m_frame->AddGeometry(new CPayphoneLight(m_frame)); 
    m_frame->AddGeometry(new CTrafficLight(m_frame)); 

    Log.infoln("CDisc::CDisc: Initial allocations complete, %u byte remaining", FreeRam());
}

CDisc::~CDisc()
{
    Log.infoln("CDisc::~CDisc: Destructing");

    ShutDown();

    delete m_frame;
}

void CDisc::Show()
{
    m_frame->Show();
    for(auto geom : m_frame->GetGeometries()) 
    {
        geom->Continue(); 
    }

    FastLED.show();
}

void CDisc::Continue()
{
    s_iteration++;

    Show();
    FastLED.countFPS();

    // Diagnostics
    size_t now = millis();

    static size_t last_log = 0;
    if(now - last_log >= 10000)
    {
        last_log = now;
        char logString[128];
        sprintf(logString, "CDisc::Continue: Frame rate for last 10 seconds is %ufps", FastLED.getFPS());
        Log.infoln(logString);
    }

    if(now - m_last_indicator >= c_indicator_delay_ms)
    {
        m_indicator_on   = !m_indicator_on;
        m_last_indicator = now;
        digitalWrite(Addressing::c_indicator_pin, m_indicator_on ? HIGH : LOW);
    }
}
