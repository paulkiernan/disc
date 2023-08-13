#include "logging.h"
#include <ArduinoLog.h>

// Formats the current runtime ms into HOURS:MINUTES:SECONDS:MILLISECONDS
void printTimestamp(Print* _logOutput) {
  char c[19];
  uint32_t ms = millis();
  uint32_t allSeconds=ms/1000;
  uint32_t secsRemaining=allSeconds%3600;
  uint32_t runHours= allSeconds/3600;
  uint32_t runMinutes=secsRemaining/60;
  uint32_t runSeconds=secsRemaining%60;
  uint32_t runMillis=ms%1000;
  sprintf(c,"%02d:%02d:%02d:%03d",runHours,runMinutes,runSeconds,runMillis);
  _logOutput->print(c);
}

// Logs the framerate of the FastLED loop on every `seconds`
static inline void logFPS(const int seconds) {
  static uint32_t lastMillis;
  static uint32_t frameCount;
  static uint16_t framesPerSecond;

  uint32_t now = millis();
  frameCount ++;
  if (now - lastMillis >= seconds * 1000) {
    framesPerSecond = frameCount / seconds;
    Log.traceln("fps: %u", framesPerSecond);
    frameCount = 0;
    lastMillis = now;
  }
}

// Blinks the on-board LED every `milliseconds`
static inline void blinkLED(const int ledPin, const int milliseconds) {
  static uint32_t lastMillis;
  static uint8_t ledState;

  pinMode(ledPin, OUTPUT);

  uint32_t now = millis();
  if (now - lastMillis >= milliseconds) {
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
    lastMillis = now;
  }
}
