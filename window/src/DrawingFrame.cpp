#include "DrawingFrame.h"
#include "ColorPalette.h"
#include "Logging.h"

#include <FastLED.h>

CDrawingFrame::CDrawingFrame(const size_t width, const size_t height, struct CRGB* leds)
{
    Log.infoln("CDrawingFrame::CDrawingFrame: Initializing Frame");
    m_grid_width = width;
    m_grid_height = height;
    p_leds = leds;

    // Draw the backgrouns - but only once
    for( size_t y = 0; y < m_grid_height; y++) {
      for( size_t x = 0; x < m_grid_width; x++) {
        size_t index = XYSafe(x, y);

        p_leds[index] = ColorPalette::DominantWindowColor;
      }
    }
}

CDrawingFrame::~CDrawingFrame()
{
    Log.infoln("CDrawingFrame::~CDrawingFrame: Destructing");
}

void CDrawingFrame::Show()
{
}

void CDrawingFrame::Delay(size_t ms)
{
  FastLED.delay(ms);
}

void CDrawingFrame::SetPixel(size_t index, CRGB rgb)
{
  p_leds[index] = rgb;
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
    size_t reverseX = (m_grid_width - 1) - x;
    i = (y * m_grid_width) + reverseX;
  } else {         // Even rows run forwards
    i = (y * m_grid_width) + x;
  }

  return i;
}

// XYSafe(x,y) takes x and y coordinates and returns an LED index number, for
// use like this:  leds[ XYSafe(x,y) ] == CRGB::Red;
//     Error checking IS performed on the ranges of x and y, and an index of
//     "-1" is returned. 
size_t CDrawingFrame::XYSafe( size_t x, size_t y){
  if( x >= m_grid_width)
  {
    Log.info("got a -1 on the x");
    return -1;
  }
  if( y >= m_grid_height){
    Log.info("got a -1 on the y");
    return -1;
  }
  return XY(x,y);
}

// XYSafeInverted(x,y) takes x and y coordinates and returns an LED index
// number, for use like this:  leds[ XYSafeInverted(x,y) ] == CRGB::Red;
//
// This function exists alongside the XYSafe(x, y) function simply because the 
// the X/Y orientation of the window we're trying to draw on is inverted and
// it's much easier for a human to reason about a coordinate system starting
// from (0, 0) vs ANYTHING else.
//
//     Error checking IS performed on the ranges of x and y, and an index of
//     "-1" is returned. 
size_t CDrawingFrame::XYSafeInverted( size_t x, size_t y){
  return XYSafe(m_grid_width - x - 1,m_grid_height - y - 1);
}