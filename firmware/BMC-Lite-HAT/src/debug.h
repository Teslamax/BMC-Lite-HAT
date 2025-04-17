#include <Arduino.h>

#define logError(fmt, ...)   \
  do { if (cdcLogLevel >= 0) { Serial.print(CDC_ERROR_PREFIX); Serial.printf_P(PSTR(fmt), ##__VA_ARGS__); Serial.println(); } } while(0)

#define logWarn(fmt, ...)    \
  do { if (cdcLogLevel >= 1) { Serial.print(CDC_WARN_PREFIX);  Serial.printf_P(PSTR(fmt), ##__VA_ARGS__); Serial.println(); } } while(0)

#define logInfo(fmt, ...)    \
  do { if (cdcLogLevel >= 2) { Serial.print(CDC_INFO_PREFIX);  Serial.printf_P(PSTR(fmt), ##__VA_ARGS__); Serial.println(); } } while(0)

#define logVerbose(fmt, ...) \
  do { if (cdcLogLevel >= 3) { Serial.print(CDC_VERBOSE_PREFIX); Serial.printf_P(PSTR(fmt), ##__VA_ARGS__); Serial.println(); } } while(0)
