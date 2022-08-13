/*  OctoWS2811 + FastLED Teensy 4.0 Window Controller 

  Required Connections
  --------------------
    pin 4:  LED Strip #1
    pin 3:  LED Strip #2
    pin 2:  LED Strip #3
*/

#include "Disc.h"
#include "CTeensy4Controller.h"
#include "Logging.h"

#include <FastLED.h>
#include <ArduinoLog.h>
#include <Arduino.h>

#include <set>
#include <map>
 
//#define DISABLE_LOGGING 
#define BRIGHTNESS 255 

// Any group of digital pins may be used

// Const Coordinates for fixed objects
struct Point{
  int x;
  int y;
};
inline bool operator<(const Point& P1, const Point& P2){
  return P1.x < P2.x || (P1.x == P2.x && P1.y < P2.y);
}
std::set<Point> streetLightCoordinatesHuman = {
  {0,  0}, {1,  0},
  {0,  1}, {1,  1}, {2,  1},
  {0,  2}, {1,  2}, {2,  2},
  {0,  3}, {1,  3}, {2,  3}, {3,  3},
  {0,  4}, {1,  4}, {2,  4}, {3,  4},
  {0,  5}, {1,  5}, {2,  5}, {3,  5}, {4,  5},
  {0,  6}, {1,  6}, {2,  6}, {3,  6}, {4,  6},
  {0,  7}, {1,  7}, {2,  7}, {3,  7}, {4,  7}, {5,  7},
  {0,  8}, {1,  8}, {2,  8}, {3,  8}, {4,  8}, {5,  8},
  {0,  9}, {1,  9}, {2,  9}, {3,  9}, {4,  9}, {5,  9}, {6,  9},
  {0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {6, 10},
  {0, 11}, {1, 11}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 11}, {7, 11}
};
std::set<Point> streetLightCoordinates; 
std::map<uint32_t, CRGB> pixelDefaultColors;

void setup() {
  delay(500);

  Serial.begin(9600);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
  Log.setPrefix(printTimestamp);

  /*
  // Translate coordinates 
  for (auto itr = streetLightCoordinatesHuman.begin(); itr != streetLightCoordinatesHuman.end(); itr++){
    Point flippedCoord = {kMatrixWidth - itr->x - 1, kMatrixHeight - itr->y -1};
    streetLightCoordinates.insert(flippedCoord);
    Log.noticeln("flipped coord: %u, %u", flippedCoord.x, flippedCoord.y);
  }
  */
}

/*

void flicker(std::set<Point> coords){
  int number_flickers = random(2, 6);
  std::map<uint32_t, CRGB> originalColors;

  for (int i=0; i < number_flickers; i++) {

    for (auto itr = coords.begin(); itr != coords.end(); itr++){
      uint16_t index = XYsafe(itr->x, itr->y);
      originalColors[index] = ledarray[index];
      ledarray[index] = blend(pixelDefaultColors[index], CRGB::Black, 200);
    }

    FastLED.show();
    int delay_ms = random(50, 100);
    FastLED.delay(delay_ms);

    for (auto itr = coords.begin(); itr != coords.end(); itr++){
      uint16_t index = XYsafe(itr->x, itr->y);
      ledarray[index] = originalColors[index];
    }
    FastLED.show();
  }
}

void DrawOneFrame(){
}
*/

void loop(){

  while(!CDisc::Instance().ShuttingDown())
  {
      CDisc::Instance().Continue();
  }

  /*

  uint32_t ms = millis();
  DrawOneFrame(); 

  long random_5000 = random(5000);
  if(random_5000 <= 1){
    flicker(streetLightCoordinates);
  } 

  FastLED.show();
  */
}