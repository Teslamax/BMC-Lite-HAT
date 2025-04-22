#include <Adafruit_MCP23X17.h>
#include "buttons.h"
#include "pinmap.h"

extern Adafruit_MCP23X17 mcp;  // if declared globally elsewhere

static uint8_t lastStableState = 0xFF;
static uint8_t debounceState = 0xFF;
static unsigned long lastDebounceTime = 0;
static const unsigned long debounceInterval = 30;  // ms

bool EXP_SIGNAL_SHUTDOWN = true;  // true = not pressed (pulled-up)
bool EXP_SIGNAL_REBOOT   = true;
bool EXP_SIGNAL_USER1    = true;


void checkButtons() {
  uint8_t currentState = 0;

  // Read each raw button input (active LOW)
  currentState |= (mcp.digitalRead(EXP_BUTTON_RAW_SHUTDOWN) ? 1 << 0 : 0);
  currentState |= (mcp.digitalRead(EXP_BUTTON_RAW_REBOOT)   ? 1 << 1 : 0);
  currentState |= (mcp.digitalRead(EXP_BUTTON_RAW_USER1)    ? 1 << 2 : 0);

  unsigned long now = millis();

  // If state changed, reset debounce timer
  if (currentState != debounceState) {
    debounceState = currentState;
    lastDebounceTime = now;
    return;
  }

  // Only process if debounce interval has passed and stable
  if ((now - lastDebounceTime) >= debounceInterval && currentState != lastStableState) {
    for (int i = 0; i < 3; i++) {
      bool wasUp = lastStableState & (1 << i);
      bool isUp  = currentState     & (1 << i);

      if (wasUp != isUp) {
        Serial.print("🔘 Button ");
        switch (i) {
          case 0: Serial.print("SHUTDOWN"); break;
          case 1: Serial.print("REBOOT");   break;
          case 2: Serial.print("USER1");    break;
        }
        Serial.println(isUp ? " released" : " pressed");
      }
    }

    lastStableState = currentState;

    EXP_SIGNAL_SHUTDOWN = (currentState & (1 << 0)) != 0;
    EXP_SIGNAL_REBOOT   = (currentState & (1 << 1)) != 0;
    EXP_SIGNAL_USER1    = (currentState & (1 << 2)) != 0;
  }
}
