#include <Arduino.h>
#include "pinmap.h"
#include "status_led.h"
#include "uart_parser.h"
#include "buttons.h"

void setup() {
  Serial.begin(115200);
  initStatusLED();
  initButtons();
  initUARTParser();
  setSystemState(STATE_BOOTING);
}

void loop() {
  updateStatusLED();
  checkButtons();
  parseUART();
}
