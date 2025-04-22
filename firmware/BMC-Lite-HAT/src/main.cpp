#include <Arduino.h>
#include "config.h"
#include "pinmap.h"
#include "status_led.h"
#include "debug.h"
#include "uart_parser.h"
#include "buttons.h"
#include "oled.h"

/*
void setup() {
  initSerialInterfaces();
  
  Wire.begin();            // uses GP6/GP7 by default on the XIAO
  
  initStatusLED();

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);


//  initButtons();

  initUARTParser();
//  setSystemState(STATE_BOOTING);

  initDisplay();
  drawHUD();  // Initial screen
}



void loop() {
  updateStatusLED();
  updateCdcActivityLED();
//  checkButtons();
  parseUART();
}
*/





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