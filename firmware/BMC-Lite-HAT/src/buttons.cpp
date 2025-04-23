// src/buttons.cpp

#include <Adafruit_MCP23X17.h>
#include "buttons.h"
#include "pinmap.h"
#include "oled.h"

// —––––––––––––––––––––––––––––––––––––––––––––––––
// 1) Define the single global expander object:
// —––––––––––––––––––––––––––––––––––––––––––––––––
Adafruit_MCP23X17 mcp;

// —––––––––––––––––––––––––––––––––––––––––––––––––
// 2) Logical state variables (debounced)
// —––––––––––––––––––––––––––––––––––––––––––––––––
bool EXP_SIGNAL_SHUTDOWN = true;  // true = released (pulled-up)
bool EXP_SIGNAL_REBOOT   = true;
bool EXP_SIGNAL_USER1    = true;

// —––––––––––––––––––––––––––––––––––––––––––––––––
// 3) Initialization — must be called from setup()
// —––––––––––––––––––––––––––––––––––––––––––––––––
void initButtons() {
  // start I²C comms at address 0x20
  if (! mcp.begin_I2C(MCP23017_I2C_ADDR) ) {
    Serial.println("❌ MCP23017 init failed");
    return;
  }

  // configure each button pin as input+pullup
  mcp.pinMode(EXP_BUTTON_RAW_SHUTDOWN, INPUT_PULLUP);
  mcp.pinMode(EXP_BUTTON_RAW_REBOOT,   INPUT_PULLUP);
  mcp.pinMode(EXP_BUTTON_RAW_USER1,    INPUT_PULLUP);

  // configure each output pin as output
  mcp.pinMode(EXP_GPIO_SIG_SHUTDOWN, OUTPUT);
  mcp.pinMode(EXP_GPIO_SIG_REBOOT,   OUTPUT);
  mcp.pinMode(EXP_GPIO_SIG_USER1,    OUTPUT);

  Serial.println("✅ Buttons initialized");
}

// —––––––––––––––––––––––––––––––––––––––––––––––––
// 4) Debounce & edge-detect; call from loop()
// —––––––––––––––––––––––––––––––––––––––––––––––––
static uint8_t lastStableState   = 0xFF;
static uint8_t debounceState     = 0xFF;
static unsigned long lastBounce  = 0;
static const unsigned long dbInt = 30;  // ms

void checkButtons() {
  uint8_t current = 0;
  current |= (mcp.digitalRead(EXP_BUTTON_RAW_SHUTDOWN) ? 1<<0 : 0);
  current |= (mcp.digitalRead(EXP_BUTTON_RAW_REBOOT)   ? 1<<1 : 0);
  current |= (mcp.digitalRead(EXP_BUTTON_RAW_USER1)    ? 1<<2 : 0);

  unsigned long now = millis();
  if (current != debounceState) {
    debounceState = current;
    lastBounce    = now;
    return;
  }
  if (now - lastBounce < dbInt) return;

  // stable new state & different from last
  if (current != lastStableState) {
    for (int i = 0; i < 3; i++) {
      bool wasUp = lastStableState & (1 << i);
      bool isUp  = current      & (1 << i);
      if (wasUp != isUp) {
        Serial.print("🔘 Button ");
        Serial.print( i==0 ? "SHUTDOWN" : i==1 ? "REBOOT" : "USER1" );
        Serial.println(isUp ? " released" : " pressed");
      }
    }
    lastStableState = current;

    // update your logical state variables
    EXP_SIGNAL_SHUTDOWN =  (current & (1<<0)) != 0;
    EXP_SIGNAL_REBOOT   =  (current & (1<<1)) != 0;
    EXP_SIGNAL_USER1    =  (current & (1<<2)) != 0;

    // drive the expander outputs to mirror the debounced state
    mcp.digitalWrite(EXP_GPIO_SIG_SHUTDOWN, EXP_SIGNAL_SHUTDOWN ? HIGH : LOW);
    mcp.digitalWrite(EXP_GPIO_SIG_REBOOT,   EXP_SIGNAL_REBOOT   ? HIGH : LOW);
    mcp.digitalWrite(EXP_GPIO_SIG_USER1,    EXP_SIGNAL_USER1    ? HIGH : LOW);
  
    // **NEW** refresh OLED status
    drawButtonStatus();
  }
}
