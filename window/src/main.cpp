/*  OctoWS2811 + FastLED Teensy 4.0 Window Controller 

  Required Connections
  --------------------
    pin 4:  LED Strip #1
    pin 3:  LED Strip #2
    pin 2:  LED Strip #3
*/

#include "CTeensy4Controller.h"
#include "logging.h"
#include <OctoWS2811.h>
#include <FastLED.h>
#include <ArduinoLog.h>
#include <Arduino.h>
#include <set>
 
//#define DISABLE_LOGGING 
#define BRIGHTNESS 255 

// Any group of digital pins may be used
const uint8_t numPins = 3;
const uint8_t pinList[numPins] = {4, 3, 2};

const uint8_t ledsPerSection = 27;
const uint8_t sectionsPerStrip = 4;
const uint8_t ledsPerStrip = ledsPerSection * sectionsPerStrip;
const uint8_t bytesPerLED = 4;  // RGBW = one byte per RGB+W
const uint8_t kMatrixWidth = ledsPerSection;
const uint8_t kMatrixHeight = 12;
const uint8_t diagnosticLED = LED_BUILTIN; 

// Const Coordinates for fixed objects
struct Point{
  int x;
  int y;
};
inline bool operator<(const Point& P1, const Point& P2){
  return P1.x < P2.x || (P1.x == P2.x && P1.y < P2.y);
}
std::set<Point> streetLightCoordinatesHuman = {
  {0,0}, {1,0},
  {0,1}, {1,1}, {2,1},
  {0,2}, {1,2}, {2,2},
  {0,3}, {1,3}, {2,3}, {3,3},
  {0,4}, {1,4}, {2,4}, {3,4},
  {0,5}, {1,5}, {2,5}, {3,5}, {4,5},
  {0,6}, {1,6}, {2,6}, {3,6}, {4,6},
  {0,7}, {1,7}, {2,7}, {3,7}, {4,7}, {5,7},
  {0,8}, {1,8}, {2,8}, {3,8}, {4,8}, {5,8},
  {0,9}, {1,9}, {2,9}, {3,9}, {4,9}, {5,9}, {6, 9},
  {0,10}, {1,10}, {2,10}, {3,10}, {4,10}, {5,10}, {6, 10},
  {0,11}, {1,11}, {2,11}, {3,11}, {4,11}, {5,11}, {6, 11}, {7, 11}
};
std::set<Point> streetLightCoordinates; 

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
DMAMEM int displayMemory[ledsPerStrip * numPins * bytesPerLED / 4];
int drawingMemory[ledsPerStrip * numPins * bytesPerLED / 4];
CRGB ledarray[numPins * ledsPerStrip];
OctoWS2811 octo(
  ledsPerStrip,
  displayMemory,
  drawingMemory,
  WS2811_RGB | WS2813_800kHz,
  numPins,
  pinList
);
CTeensy4Controller<BGR, WS2813_800kHz> *pcontroller;

void setup() {
  Serial.begin(9600);
  Log.begin   (LOG_LEVEL_VERBOSE, &Serial);
  Log.setPrefix(printTimestamp);

  // Translate coordinates 
  for (auto itr = streetLightCoordinatesHuman.begin(); itr != streetLightCoordinatesHuman.end(); itr++){
    Point flippedCoord = {kMatrixWidth - itr->x - 1, kMatrixHeight - itr->y -1};
    streetLightCoordinates.insert(flippedCoord);
    Log.noticeln("flipped coord: %u, %u", flippedCoord.x, flippedCoord.y);
  }

  Log.noticeln("DISC Window Initializing");
  octo.begin();
  pcontroller = new CTeensy4Controller<BGR, WS2813_800kHz>(&octo);
  FastLED.setBrightness(255);
  FastLED.addLeds(pcontroller, ledarray, numPins * ledsPerStrip);
  Log.noticeln("OCTOWS2811 and FastLED Initialized!");
}

// XY(x,y) takes x and y coordinates and returns an LED index number, for use
// like this:  leds[ XY(x,y) ] == CRGB::Red;
//     No error checking is performed on the ranges of x and y.
uint16_t XY( uint8_t x, uint8_t y){
  uint16_t i;
  
  if( y & 0x01) {  // Odd rows run backwards
    uint8_t reverseX = (kMatrixWidth - 1) - x;
    i = (y * kMatrixWidth) + reverseX;
  } else {         // Even rows run forwards
    i = (y * kMatrixWidth) + x;
  }

  return i;
}

// XYsafe(x,y) takes x and y coordinates and returns an LED index number, for
// use like this:  leds[ XYsafe(x,y) ] == CRGB::Red;
//     Error checking IS performed on the ranges of x and y, and an index of
//     "-1" is returned. 
uint16_t XYsafe( uint8_t x, uint8_t y){
  if( x >= kMatrixWidth) return -1;
  if( y >= kMatrixHeight) return -1;
  return XY(x,y);
}

void DrawPassingCar( uint16_t mls ){
}

void DrawOneFrame( uint16_t mls ){
  for( uint8_t y = 0; y < kMatrixHeight; y++) {
    for( uint8_t x = 0; x < kMatrixWidth; x++) {

      // Draw background light 
      if (y <= 2) {
        ledarray[XYsafe(x, y)] = CRGB::DarkSlateBlue;
      } else if (y >= kMatrixHeight - 1) {
        ledarray[XYsafe(x, y)] = CRGB::PaleVioletRed;
      } else {
        ledarray[XYsafe(x, y)] = CRGB::DarkOrchid;
      }

      // Draw artifacts like ambient streetlamps, etc.
      if (streetLightCoordinates.find({x, y}) != streetLightCoordinates.end()){
        //Log.noticeln("working: %u, %u", x, y);
        ledarray[XYsafe(x, y)] = CRGB::DarkGoldenrod;
      }
    }
  }
}

// Draw a rainbow circle - are we fitting in yet?!
void loop(){
  blinkLED(diagnosticLED, 500);
  logFPS(1);

  uint32_t ms = millis();
  DrawOneFrame(ms); 

  FastLED.show();
}