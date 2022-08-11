/*  OctoWS2811 + FastLED Teensy LC Sewer Controller 

  Required Connections
  --------------------
    pin 5:  LED Strip #1
    pin 6:  LED Strip #2
    pin 7:  LED Strip #3
    pin 8:  LED Strip #3

  OctoWS2811 requires the following mapping of pins for Teensy LC-3.6 formats:
    * LED Strip #1: pin 2
    * LED Strip #2: pin 14
    * LED Strip #3: pin 7
    * LED Strip #4: pin 8
    * LED Strip #5: pin 6
    * LED Strip #6: pin 20
    * LED Strip #7: pin 21
    * LED Strip #8: pin 5

  We, instead, design around minimised board layout constraints and only use
  pins 5, 6, 7, 8. Drawing memory is allocated for ((longest strip) * 8 *
  bytes_per_led). This means we need to irregularly index the drawing memory to
  accurately draw out subject.

  See https://www.pjrc.com/teensy/td_libs_OctoWS2811.html for more information.
*/

#include "CTeensyLCController.h"
#include "logging.h"
#include <OctoWS2811.h>
#include <FastLED.h>
#include <ArduinoLog.h>
#include <Arduino.h>
 
//#define DISABLE_LOGGING 
#define BRIGHTNESS 255 
#define NUM_PINS 8 
#define LOG_LEVEL LOG_LEVEL_VERBOSE

const uint8_t actualLEDsPerStrip = 19;
const uint8_t ledsPerStrip = actualLEDsPerStrip + 1;
const uint8_t bytesPerLED = 3;  // RGB = one byte per RGB
const uint8_t diagnosticLED = LED_BUILTIN; 

// These buffers need to be large enough for all the pixels.
// The total number of pixels is "ledsPerStrip * NUM_PINS".
// Each pixel needs 4 bytes, so multiply by 4.  An "int" is
// 4 bytes, so divide by 4.  The array is created using "int"
// so the compiler will align it to 32 bit memory.
DMAMEM int displayMemory[ledsPerStrip * NUM_PINS * bytesPerLED / 4];
int drawingMemory[ledsPerStrip * NUM_PINS * bytesPerLED / 4];

// Setup the following drawing spaces:
//   * CRGB array the main program writes changes to
//   * OctoWS2811 pointer for syncing LED values to strip
//   * CTeensyLCController - FastLED->OctoWS2811 bridge controller
CRGB ledarray[NUM_PINS * ledsPerStrip];
OctoWS2811 octo(
  ledsPerStrip,
  displayMemory,
  drawingMemory,
  WS2811_RGB | WS2811_800kHz
);
CTeensyLCController<RBG, WS2811_800kHz> *pcontroller;

void setup() {
  Serial.begin(9600);
  Log.begin   (LOG_LEVEL, &Serial);
  Log.setPrefix(printTimestamp);

  Log.noticeln("DISC Sewer Initializing");
  octo.begin();
  pcontroller = new CTeensyLCController<RBG, WS2811_800kHz>(&octo);
  FastLED.setBrightness(255);
  FastLED.addLeds(pcontroller, ledarray, NUM_PINS * ledsPerStrip);
  Log.noticeln("OCTOWS2811 and FastLED Initialized!");
}

void DrawOneFrame(uint32_t ms){
  if( ms < 10000 ) {
    FastLED.setBrightness( scale8( BRIGHTNESS, (ms * 256) / 10000));
  } else {
    FastLED.setBrightness(BRIGHTNESS);
  }

  for( uint8_t y = 0; y < ledsPerStrip * NUM_PINS; y++) {
    ledarray[y]  = CRGB::Green; 
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