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
    display.setTextSize(1);
    display.setCursor(0, 32);  // adjust Y as needed
    display.fillRect(0, 32, 128, 16, BLACK);  // clear previous status area
  
    display.print("BTN: ");
    display.print("S=");
    display.print(EXP_SIGNAL_SHUTDOWN ? "✓" : "✗");
    display.print(" R=");
    display.print(EXP_SIGNAL_REBOOT ? "✓" : "✗");
    display.print(" U=");
    display.print(EXP_SIGNAL_USER1 ? "✓" : "✗");
  
    display.display();
  }