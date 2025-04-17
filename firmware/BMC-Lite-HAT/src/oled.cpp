// oled.cpp
#include "oled.h"
#include "pinmap.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
    Serial.println("❌ OLED init failed");
    return;
  }
  display.clearDisplay();
  display.display();
}

void drawHUD() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("BMC Lite HAT");
  display.println("State: RUNNING");
  display.display();
}

void showPopup(const char *msg) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 16);
  display.println(msg);
  display.display();
  delay(1500);  // hold briefly
  drawHUD();    // return to normal screen
}
