/*  OctoWS2812 + FastLED Teensy LC Sewer Controller 

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

const uint8_t actualLEDsPerStrip = 29;
const uint8_t ledsPerStrip = actualLEDsPerStrip + 1;
const uint8_t bytesPerLED = 3;  // RGB = one byte per RGB
const uint8_t diagnosticLED = LED_BUILTIN; 

// Colour + pulse starting and ending conditions 
const uint8_t hueStart = 50 * (360/255); 
const uint8_t hueEnd = 95 * (360/255); 
const uint8_t satStart = 255;
const uint8_t satEnd = 255;
const float_t valueMin = 200.0; 
const float_t valueMax = BRIGHTNESS;
const float_t pulseSpeed = 0.80;
const float_t delta = (valueMax - valueMin) / 2.35040238;

// Volatile Working Colour Space
volatile uint8_t hue = hueStart;
volatile uint8_t sat = satStart;
volatile float_t val = valueMin;

// These buffers need to be large enough for all the pixels.
// The total number of pixels is "ledsPerStrip * NUM_PINS".
// Each pixel needs 4 bytes, so multiply by 4.  An "int" is
// 4 bytes, so divide by 4.  The array is created using "int"
// so the compiler will align it to 32 bit memory.
//
// Setup the following drawing spaces:
//   * CRGB array the main program writes changes to
//   * OctoWS2811 pointer for syncing LED values to strip
//   * CTeensyLCController - FastLED->OctoWS2811 bridge controller
DMAMEM int displayMemory[ledsPerStrip * NUM_PINS * bytesPerLED / 4];
int drawingMemory[ledsPerStrip * NUM_PINS * bytesPerLED / 4];
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
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds(pcontroller, ledarray, NUM_PINS * ledsPerStrip);
  Log.noticeln("OCTOWS2811 and FastLED Initialized!");
}

// Draw a glowing effect, pulsing the under-grate lights between yellow and
// green
void DrawSewerFrame(uint32_t ms){
  float dV = ((exp(sin(pulseSpeed * ms/2000.0*PI)) -0.36787944) * delta);
  val = valueMin + dV;
  hue = map(val, valueMin, valueMax, hueStart, hueEnd);
  sat = map(val, valueMin, valueMax, satStart, satEnd);

  for (int i = ledsPerStrip * 7; i < (ledsPerStrip * 7) + ledsPerStrip; i++) {
    ledarray[i] = CHSV(hue, sat, val);
    ledarray[i].r = dim8_video(ledarray[i].r);
    ledarray[i].g = dim8_video(ledarray[i].g);
    ledarray[i].b = dim8_video(ledarray[i].b);
  }
}

// Main program loop
//   1. Blink diagnostic LED
//   2. Log the draw-loop frame rate
//   3. Stage a draw frame of the sewer light
//   4. Show all frames 
void loop(){
  blinkLED(diagnosticLED, 500);
  logFPS(1);

  uint32_t ms = millis();
  DrawSewerFrame(ms);

  FastLED.show();
}