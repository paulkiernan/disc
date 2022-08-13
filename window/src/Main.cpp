/*  OctoWS2811 + FastLED Teensy 4.0 Window Controller 

  Required Connections
  --------------------
    pin 4:  LED Strip #1
    pin 3:  LED Strip #2
    pin 2:  LED Strip #3
*/

#include "Disc.h"
#include "Logging.h"

#include <ArduinoLog.h>
#include <Arduino.h>

void setup()
{
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

void loop()
{
  while(!CDisc::Instance().ShuttingDown())
  {
      CDisc::Instance().Continue();
  }
}