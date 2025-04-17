#pragma once
#include <Arduino.h>
#include "status_led.h"   // for setSystemState() and SystemState

void initUARTParser();
void parseUART();
