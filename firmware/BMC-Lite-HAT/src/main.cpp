#include <Arduino.h>
#include "pinmap.h"
#include "status_led.h"
#include "uart_parser.h"
#include "buttons.h"

void setup() {
  Serial.begin(115200);
  while(!Serial);          // wait for the USB‑CDC console
  Wire.begin();            // uses GP6/GP7 by default on the XIAO

  Serial.println("I²C Scan:");
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print(" • Found 0x");
      Serial.println(addr, HEX);
    }
  }
  Serial.println("Scan complete.");//  initStatusLED();
//  initButtons();
//  initUARTParser();
//  setSystemState(STATE_BOOTING);
}

void loop() {
//  updateStatusLED();
//  checkButtons();
//  parseUART();
}






/*
#include <Arduino.h>
#include <Wire.h>

#include "pinmap.h"
#include "status_led.h"
#include "uart_parser.h"
#include "buttons.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial1.begin(115200);        // Pi’s UART on GP0/GP1
  initStatusLED();              // your NeoPixel setup
  initButtons();                // if you’re testing buttons
  initUARTParser();             // reserve buffer, etc.

  setSystemState(STATE_BOOTING);
}

void loop() {
  parseUART();                  // relay + parse → drive state machine
  updateStatusLED();            // drive your NeoPixel based on currentState
  checkButtons();               // if you want button‑driven overrides
}
*/