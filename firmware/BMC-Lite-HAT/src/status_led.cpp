#include "status_led.h"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(1, NEOPIXEL_DATA_PIN, NEO_GRB + NEO_KHZ800);
SystemState currentState = STATE_OFF;

void initStatusLED() {
  // 1. Set the power-enable pin HIGH
  pinMode(NEOPIXEL_POWER_PIN, OUTPUT);
  digitalWrite(NEOPIXEL_POWER_PIN, HIGH);  // Turn on power to the NeoPixel

  // 2. Initialize the NeoPixel object
  strip.begin();
  strip.show();
}

void setSystemState(SystemState state) {
  currentState = state;
}

void updateStatusLED() {
  static unsigned long lastUpdate = 0;
  static bool ledOn = true;
  unsigned long now = millis();
  uint32_t color = 0;
  uint8_t mode = 0;  // 0 = solid, 1 = blink, 2 = breathe
  
  switch (currentState) {
    case STATE_BOOTING:
      color = strip.Color(255, 128, 0); mode = 2; break;  // Orange, breathing
    case STATE_RUNNING:
      color = strip.Color(0, 255, 0);   mode = 0; break;  // Green, solid
    case STATE_SHUTTING_DOWN:
      color = strip.Color(255, 255, 0); mode = 1; break;  // Yellow, blinking
    case STATE_HALTED:
      color = strip.Color(255, 0, 0);   mode = 1; break;  // Red, blinking
    case STATE_CRASH:
      color = strip.Color(255, 0, 255); mode = 1; break;  // Magenta, blinking
    case STATE_UNRESPONSIVE:
      color = strip.Color(128, 64, 0);  mode = 2; break;  // Amber, breathing
    default:
      color = 0; mode = 0; break;
  }
  if (mode == 0) {
    // Solid color
    strip.setPixelColor(0, color);
  }
  else if (mode == 1) {
    // Blink on/off every 500ms
    if (now - lastUpdate > 500) {
      lastUpdate = now;
      ledOn = !ledOn;
    }
    strip.setPixelColor(0, ledOn ? color : 0);
  }
  else if (mode == 2) {
    // Breathing: slow pulse using sine wave (1.5s cycle)
    float t = (now % 1500) / 1500.0 * PI;
    float brightness = (sin(t) + 1.0) / 2.0;  // 0 → 1
  
    // Extract base RGB
    uint8_t r = (uint8_t)((color >> 16) & 0xFF);
    uint8_t g = (uint8_t)((color >> 8) & 0xFF);
    uint8_t b = (uint8_t)(color & 0xFF);
  
    // Apply brightness scale
    strip.setPixelColor(0,
      (uint8_t)(r * brightness),
      (uint8_t)(g * brightness),
      (uint8_t)(b * brightness));
  }
  strip.show();
  }
