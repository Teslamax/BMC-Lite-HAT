// oled.cpp
#include "oled.h"
#include "pinmap.h"
#include "buttons.h"

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

void drawButtonStatus() {
    // clear the lower region (adjust Y as needed)
    const int y0 = 48, h = 16;
    display.fillRect(0, y0, display.width(), h, SSD1306_BLACK);
  
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, y0 + 0);
  
    display.print("S:");
    display.print(EXP_SIGNAL_SHUTDOWN ? "1" : "0");
    display.print(" R:");
    display.print(EXP_SIGNAL_REBOOT   ? "1" : "0");
    display.print(" U:");
    display.print(EXP_SIGNAL_USER1    ? "1" : "0");
  
    display.display();
  }