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

// These buffers need to be large enough for all the pixels.
// The total number of pixels is "ledsPerStrip * numPins".
// Each pixel needs 4 bytes, so multiply by 4.  An "int" is
// 4 bytes, so divide by 4.  The array is created using "int"
// so the compiler will align it to 32 bit memory.
DMAMEM int displayMemory[ledsPerStrip * numPins * bytesPerLED / 4];
int drawingMemory[ledsPerStrip * numPins * bytesPerLED / 4];

// Setup the following drawing spaces:
//   * CRGB array the main program writes changes to
//   * OctoWS2811 pointer for syncing LED values to strip
//   * CTeensy4Controller - FastLED->OctoWS2811 bridge controller
CRGB ledarray[numPins * ledsPerStrip];
OctoWS2811 octo(
  ledsPerStrip,
  displayMemory,
  drawingMemory,
  WS2811_BGR | WS2811_800kHz,
  numPins,
  pinList
);
CTeensy4Controller<BGR, WS2811_800kHz> *pcontroller;

void setup() {
  Serial.begin(9600);
  Log.begin   (LOG_LEVEL_VERBOSE, &Serial);
  Log.setPrefix(printTimestamp);

  Log.noticeln("DISC Window Initializing");
  octo.begin();
  pcontroller = new CTeensy4Controller<BGR, WS2811_800kHz>(&octo);
  FastLED.setBrightness(255);
  FastLED.addLeds(pcontroller, ledarray, numPins * ledsPerStrip);
  Log.noticeln("OCTOWS2811 and FastLED Initialized!");
}

// XY(x,y) takes x and y coordinates and returns an LED index number, for use
// like this:  leds[ XY(x,y) ] == CRGB::Red;
//     No error checking is performed on the ranges of x and y.
uint16_t XY( uint8_t x, uint8_t y){
  uint16_t i;
  
  if( y & 0x01) {
    // Odd rows run backwards
    uint8_t reverseX = (kMatrixWidth - 1) - x;
    i = (y * kMatrixWidth) + reverseX;
  } else {
    // Even rows run forwards
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

void DrawOneFrame( uint8_t startHue8, int8_t yHueDelta8, int8_t xHueDelta8){
  uint8_t lineStartHue = startHue8;
  for( uint8_t y = 0; y < kMatrixHeight; y++) {
    lineStartHue += yHueDelta8;
    uint8_t pixelHue = lineStartHue;      
    for( uint8_t x = 0; x < kMatrixWidth; x++) {
      pixelHue += xHueDelta8;
      ledarray[XYsafe(x, y)]  = CHSV( pixelHue, 255, 255);
    }
  }
}

// Draw a rainbow circle - are we fitting in yet?!
void loop(){
  blinkLED(diagnosticLED, 500);
  logFPS(1);

  uint32_t ms = millis();
  int32_t yHueDelta32 = ((int32_t)cos16( ms * (7/1) ) * (kMatrixWidth));
  int32_t xHueDelta32 = ((int32_t)cos16( ms * (14/1) ) * (kMatrixHeight));
  DrawOneFrame( ms / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);

  if( ms < 5000 ) {
    FastLED.setBrightness( scale8( BRIGHTNESS, (ms * 256) / 5000));
  } else {
    FastLED.setBrightness(BRIGHTNESS);
  }

  FastLED.show();
}