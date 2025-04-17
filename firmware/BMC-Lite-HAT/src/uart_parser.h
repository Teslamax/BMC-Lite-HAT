#pragma once

#include <Arduino.h>
#include "status_led.h"

// Initializes the parser; call once in setup()
void initUARTParser();
// Call in loop() to do both UART→USB and USB→UART
void parseUART();