/*  OctoWS2811 Teensy4 Window Controller 

  Required Connections
  --------------------
    pin 2:  LED Strip #1
*/

#include "CTeensy4Controller.h"
#include <OctoWS2811.h>
#include <FastLED.h>
#include <Arduino.h>

// Any group of digital pins may be used
const int numPins = 3;
byte pinList[numPins] = {4, 3, 2};

const int ledsPerSection = 27;
const int sectionsPerStrip = 4;
const int ledsPerStrip = ledsPerSection * sectionsPerStrip;
const int bytesPerLED = 4;  // RGBW 

// These buffers need to be large enough for all the pixels.
// The total number of pixels is "ledsPerStrip * numPins".
// Each pixel needs 4 bytes, so multiply by 4.  An "int" is
// 4 bytes, so divide by 4.  The array is created using "int"
// so the compiler will align it to 32 bit memory.
DMAMEM int displayMemory[ledsPerStrip * numPins * bytesPerLED / 4];
int drawingMemory[ledsPerStrip * numPins * bytesPerLED / 4];

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
  Serial.println("DISC Window Initializing");
  octo.begin();
  pcontroller = new CTeensy4Controller<BGR, WS2811_800kHz>(&octo);
  FastLED.setBrightness(255);
  FastLED.addLeds(pcontroller, ledarray, numPins * ledsPerStrip);
  Serial.println("OCTOWS2811 and FastLED Initialized!");
}

void loop() {
  uint16_t sinBeat = beatsin16(5, 0, (numPins * ledsPerStrip) - 1, 0, 0);
  uint8_t sinBeat2 = beatsin8(7, 0, 255, 0, 0);

  ledarray[sinBeat] = CHSV(sinBeat2, 255, 255);

  fadeToBlackBy(ledarray, (numPins * ledsPerStrip), 1);

  FastLED.show();
  Serial.println("loop complete");
}