#include "Disc.h"
#include "Logging.h"
#include "Addressing.h"
#include "Arduino.h"
#include "ColorPallete.h"
#include "FreeRam.h"
#include "GammaCorrection.h"

size_t CDisc::s_iteration = 0;
uint8_t CDisc::c_pinList[c_numPins] = {4, 3, 2};
DMAMEM int CDisc::s_displayMemory[c_ledsPerStrip * c_numPins * c_bytesPerLED / 4];
int        CDisc::s_drawingMemory[c_ledsPerStrip * c_numPins * c_bytesPerLED / 4];
CRGB       CDisc::s_ledarray[c_numPins * c_ledsPerStrip];

CDisc& CDisc::Instance()
{
    static CDisc bixi;
    return bixi;
}

CDisc::CDisc()
{
    Log.infoln("CDisc::CDisc: Initializing Bixi");
    pinMode(c_indicatorPin, OUTPUT);

    // geometry
    Log.infoln("CDisc::CDisc: Geometry = Grid");
    /*
    m_geometry = new CGrid();
    m_show = new CPixelArray(*m_geometry);
    */

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

    GammaCorrection::Init(1.50);

    Log.infoln("CDisc::CDisc: Initial allocations complete, %u byte remaining", FreeRam());
}

CDisc::~CDisc()
{
    Log.infoln("CDisc::~CDisc: Destructing");

    ShutDown();

    //delete m_geometry;
}

void CDisc::Show()
{
  for( size_t y = 0; y < c_kMatrixHeight; y++) {
    for( size_t x = 0; x < c_kMatrixWidth; x++) {
      size_t index = XYSafe(x, y);

      // Draw background light 
      CRGB col = CRGB::DarkSlateBlue;
      s_ledarray[index] = col;
    }
  }
  FastLED.show();
}

// XY(x,y) takes x and y coordinates and returns an LED index number, for use
// like this:  leds[ XY(x,y) ] == CRGB::Red;
//     No error checking is performed on the ranges of x and y.
size_t CDisc::XY( size_t x, size_t y){
  size_t i;
  
  if( y & 0x01) {  // Odd rows run backwards
    size_t reverseX = (c_kMatrixWidth - 1) - x;
    i = (y * c_kMatrixWidth) + reverseX;
  } else {         // Even rows run forwards
    i = (y * c_kMatrixWidth) + x;
  }

  return i;
}

// XYsafe(x,y) takes x and y coordinates and returns an LED index number, for
// use like this:  leds[ XYsafe(x,y) ] == CRGB::Red;
//     Error checking IS performed on the ranges of x and y, and an index of
//     "-1" is returned. 
size_t CDisc::XYSafe( size_t x, size_t y){
  if( x >= c_kMatrixWidth) return -1;
  if( y >= c_kMatrixHeight) return -1;
  return XY(x,y);
}

void CDisc::Continue()
{
    s_iteration++;

    size_t now = millis();

    //m_geometry->Continue();
    Show();

    FastLED.countFPS();

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
