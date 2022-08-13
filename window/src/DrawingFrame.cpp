#include "DrawingFrame.h"
#include "ColorPalette.h"
#include "Logging.h"

#include <FastLED.h>

CDrawingFrame::CDrawingFrame(const size_t width, const size_t height, struct CRGB* leds)
{
    Log.infoln("CDrawingFrame::CDrawingFrame: Initializing Frame");
    m_gridWidth = width;
    m_gridHeight = height;
    p_ledarray = leds;
}

CDrawingFrame::~CDrawingFrame()
{
    Log.infoln("CDrawingFrame::~CDrawingFrame: Destructing");
}

void CDrawingFrame::Show()
{
  for( size_t y = 0; y < m_gridHeight; y++) {
    for( size_t x = 0; x < m_gridWidth; x++) {
      size_t index = XYSafe(x, y);

      // Draw background light 
      p_ledarray[index] = ColorPalette::DominantWindowColor;
    }
  }

  FastLED.show();
}

void CDrawingFrame::FastLEDShow()
{
  FastLED.show();
}

void CDrawingFrame::Delay(size_t ms)
{
  FastLED.delay(ms);
}

void CDrawingFrame::SetPixel(size_t index, CRGB rgb)
{
  p_ledarray[index] = rgb;
}

void CDrawingFrame::AddGeometry(CGeometry* geom)
{
  m_geometries.push_back(geom);
}

// XY(x,y) takes x and y coordinates and returns an LED index number, for use
// like this:  leds[ XY(x,y) ] == CRGB::Red;
//     No error checking is performed on the ranges of x and y.
size_t CDrawingFrame::XY( size_t x, size_t y){
  size_t i;
  
  if( y & 0x01) {  // Odd rows run backwards
    size_t reverseX = (m_gridWidth - 1) - x;
    i = (y * m_gridWidth) + reverseX;
  } else {         // Even rows run forwards
    i = (y * m_gridWidth) + x;
  }

  return i;
}

// XYsafe(x,y) takes x and y coordinates and returns an LED index number, for
// use like this:  leds[ XYsafe(x,y) ] == CRGB::Red;
//     Error checking IS performed on the ranges of x and y, and an index of
//     "-1" is returned. 
size_t CDrawingFrame::XYSafe( size_t x, size_t y){
  if( x >= m_gridWidth) return -1;
  if( y >= m_gridHeight) return -1;
  return XY(x,y);
}
