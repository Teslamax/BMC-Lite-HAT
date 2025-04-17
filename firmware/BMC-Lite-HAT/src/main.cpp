#include <Arduino.h>
#include "config.h"
#include "pinmap.h"
#include "status_led.h"
#include "debug.h"
#include "uart_parser.h"
#include "buttons.h"
#include "oled.h"

void setup() {
  Serial.begin(115200);
  while(!Serial);          // wait for the USB‑CDC console
  logInfo("Starting BMC Lite HAT firmware v%s", FIRMWARE_VERSION);
  Wire.begin();            // uses GP6/GP7 by default on the XIAO


  initDisplay();
  drawHUD();  // Initial screen
}

//  initStatusLED();
//  initButtons();
//  initUARTParser();
//  setSystemState(STATE_BOOTING);


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
  Serial.begin(115200);        // USB‑CDC
  while (!Serial);

  Serial1.begin(115200);       // UART0 on GP0/GP1
  Wire.begin();

  initStatusLED();
  initButtons();
  initUARTParser();

  setSystemState(STATE_BOOTING);
}

void loop() {
  parseUART();             // does both relay + parsing + echo
  updateStatusLED();
  checkButtons();
}
*/