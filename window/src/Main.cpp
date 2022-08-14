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
  delay(500);  // Wait a bit to boot up, allowing the host computer to ready a
               // serial connection.

  Serial.begin(9600);
  Log.begin(LOG_LEVEL_TRACE, &Serial, true);
  Log.setPrefix(printTimestamp);
}

void loop()
{
  while(!CDisc::Instance().ShuttingDown())
  {
      CDisc::Instance().Continue();
  }
}