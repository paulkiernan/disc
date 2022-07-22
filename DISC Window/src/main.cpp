/*  OctoWS2811 Teensy4 Window Controller 

  Required Connections
  --------------------
    pin 2:  LED Strip #1
*/

#include <OctoWS2811.h>

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF

// Any group of digital pins may be used
const int numPins = 1;
byte pinList[numPins] = {2};

const int ledsPerStrip = 27;
const int bytesPerLED = 4;  // RGBW
const int config = WS2811_BGR | WS2811_800kHz;

// These buffers need to be large enough for all the pixels.
// The total number of pixels is "ledsPerStrip * numPins".
// Each pixel needs 4 bytes, so multiply by 4.  An "int" is
// 4 bytes, so divide by 4.  The array is created using "int"
// so the compiler will align it to 32 bit memory.
DMAMEM int displayMemory[ledsPerStrip * numPins * bytesPerLED / 4];
int drawingMemory[ledsPerStrip * numPins * bytesPerLED / 4];


OctoWS2811 leds(
  ledsPerStrip,
  displayMemory,
  drawingMemory,
  config,
  numPins,
  pinList
);

void setup() {
  Serial.begin(9600);
  Serial.println("DISC Window Initializing");
  leds.begin();
  leds.show();
}

void colorWipe(int color, int wait)
{
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
    leds.show();
    delayMicroseconds(wait);
  }
}

void loop() {
  int microsec = 2000000 / leds.numPixels();  // change them all in 2 seconds

  colorWipe(RED, microsec);
  colorWipe(GREEN, microsec);
  colorWipe(BLUE, microsec);
  colorWipe(YELLOW, microsec);
  colorWipe(PINK, microsec);
  colorWipe(ORANGE, microsec);
  colorWipe(WHITE, microsec);
  Serial.println("loop complete");
}