#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

#include <Arduino.h>

void printTimestamp(Print* _logOutput);
void logFPS(const int seconds);
void blinkLED(const int ledPin, const int seconds);

#endif
