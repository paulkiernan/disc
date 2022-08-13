#include "Disc.h"
#include "Logging.h"
#include "Addressing.h"
#include "Arduino.h"
#include "FreeRam.h"
#include "GammaCorrection.h"

#include "DrawingFrame.h"
#include "Geometry.h"
#include "PayphoneLight.h"

size_t CDisc::s_iteration = 0;
uint8_t CDisc::c_pinList[c_numPins] = {4, 3, 2};
DMAMEM int CDisc::s_displayMemory[c_ledsPerStrip * c_numPins * c_bytesPerLED / 4];
int        CDisc::s_drawingMemory[c_ledsPerStrip * c_numPins * c_bytesPerLED / 4];
CRGB       CDisc::s_ledarray[c_numPins * c_ledsPerStrip];

CDisc& CDisc::Instance()
{
    static CDisc disc;
    return disc;
}

CDisc::CDisc()
{
    Log.infoln("CDisc::CDisc: Initializing Disc");
    pinMode(c_indicatorPin, OUTPUT);

    // Setup OctoWS2811 and FastLED
    p_octo = new OctoWS2811(
        c_ledsPerStrip,
        s_displayMemory,
        s_drawingMemory,
        WS2811_RGB | WS2813_800kHz,
        c_numPins,
        c_pinList
    );
    p_octo->begin();
    p_controller = new CTeensy4Controller<BGR, WS2813_800kHz>(p_octo);
    FastLED.setBrightness(c_brightness);
    FastLED.addLeds(
        p_controller,
        s_ledarray,
        c_numPins * c_ledsPerStrip
    ).setCorrection(TypicalPixelString).setDither(c_brightness < 255);
    Log.noticeln("OCTOWS2811 and FastLED Initialized!");

    // Setup the scene and objects in them
    m_frame = new CDrawingFrame(
        c_ledsPerSection, // width
        c_windowHeight,   // height
        s_ledarray        // leds
    );
    m_frame->AddGeometry(new CPayphoneLight(m_frame)); 

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
    FastLED.show();
}

void CDisc::Continue()
{
    s_iteration++;

    for(auto geom : m_frame->GetGeometries()) 
    {
        geom->Continue(); 
    }
    
    Show();
    FastLED.countFPS();

    // Diagnostics
    size_t now = millis();

    static size_t last_log = 0;
    if(now - last_log >= 10000)
    {
        last_log = now;
        char logString[128];
        sprintf(logString, "CDisc::Continue: Frame rate for last 10 seconds is %u", FastLED.getFPS());
        Log.infoln(logString);
    }

    if(now - m_lastIndicator >= c_indicatorDelayMs)
    {
        m_indicatorOn   = !m_indicatorOn;
        m_lastIndicator = now;
        digitalWrite(c_indicatorPin, m_indicatorOn ? HIGH : LOW);
    }
}
