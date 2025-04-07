#include "status_led.h"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(1, LED_PIN, NEO_GRB + NEO_KHZ800);
SystemState currentState = STATE_OFF;

void initStatusLED() {
  strip.begin();
  strip.show();
}

void setSystemState(SystemState state) {
  currentState = state;
}

void updateStatusLED() {
  uint32_t color = 0;
  switch (currentState) {
    case STATE_BOOTING:        color = strip.Color(255, 128, 0); break; // Orange
    case STATE_RUNNING:        color = strip.Color(0, 255, 0); break;   // Green
    case STATE_SHUTTING_DOWN:  color = strip.Color(255, 255, 0); break; // Yellow
    case STATE_HALTED:         color = strip.Color(255, 0, 0); break;   // Red
    case STATE_CRASH:          color = strip.Color(255, 0, 255); break; // Magenta
    case STATE_UNRESPONSIVE:   color = strip.Color(128, 64, 0); break;  // Amber/Brown
    default:                   color = 0; break;
  }
  strip.setPixelColor(0, color);
  strip.show();
}
