#include "Logging.h"

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
