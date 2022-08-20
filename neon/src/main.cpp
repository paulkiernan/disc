#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 200
#define MAX_BRIGHTNESS 255
#define STEP_BRIGHTNESS 128

#define LED_STRIP_AUX 8

#define LED_PIN 13
#define CHIPSET        WS2813
#define COLOR_ORDER    GRB

int period = 1000;
CRGB led_strip_AUX[NUM_LEDS];

// Define the array of leds

int ledStripSize = 7;
int colors[] = {
  CRGB::Amethyst,
  CRGB::Brown,
  CRGB::Chartreuse,
  CRGB::Coral,
  CRGB::Crimson,
  CRGB::DarkBlue,
  CRGB::DarkCyan,
  CRGB::DarkGoldenrod,
  CRGB::DarkGreen,
  CRGB::DarkMagenta,
  CRGB::DarkOrange,
  CRGB::DarkOrchid,
  CRGB::DarkRed,
  CRGB::DarkSlateBlue,
  CRGB::FireBrick,
  CRGB::FloralWhite,
  CRGB::Gold,
  CRGB::Goldenrod,
  CRGB::HotPink,
  CRGB::IndianRed,
  CRGB::Indigo,
  CRGB::Lavender,
  CRGB::LavenderBlush,
  CRGB::LightBlue,
  CRGB::LightCoral,
  CRGB::LightSalmon,
  CRGB::LightSeaGreen,
  CRGB::Maroon,
  CRGB::MediumOrchid,
  CRGB::MediumPurple,
  CRGB::MediumVioletRed,
  CRGB::MistyRose,
  CRGB::Olive,
  CRGB::Plum,
  CRGB::LightGoldenrodYellow
};
int colorArraySize = sizeof(colors) / sizeof(int);

void flicker(int start_index, int end_index, CRGB* leds)
{
    int original_colour_r = leds[start_index].r;
    int original_colour_g = leds[start_index].g;
    int original_colour_b = leds[start_index].b;
    
    int number_flickers = random(1, 5);

    for (int i=0; i < number_flickers; i++) {

        // Turn off
        for (int j=start_index; j < end_index; j++) {
            leds[j] = 0x000000;
        }
        FastLED.show();
        int delay_ms = random(50, 100);
        delay(delay_ms);

        // Turn back on
        for (int j=start_index; j < end_index; j++) {
            leds[j].setRGB(
                original_colour_r,
                original_colour_g,
                original_colour_b
            );
        }
        FastLED.show();
    }
}

void setup() {

  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_STRIP_AUX, OUTPUT);
  FastLED.addLeds<CHIPSET, LED_STRIP_AUX, COLOR_ORDER>(
          led_strip_AUX,
          NUM_LEDS
  ).setCorrection(TypicalSMD5050);

  // Initialize with color
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
    led_strip_AUX[dot] = 0x777700;
  }
  FastLED.setBrightness(MAX_BRIGHTNESS);
  FastLED.show();
}

void loop() {
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
        led_strip_AUX[dot] = 0x777700;
    }
    digitalWrite(LED_PIN, HIGH);   // set the LED on
    delay(period);                  // wait for a second
    digitalWrite(LED_PIN, LOW);    // set the LED off
    delay(period);
    FastLED.show();
}