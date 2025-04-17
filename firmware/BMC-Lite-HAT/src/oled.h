// oled.h
#pragma once
#include <Adafruit_SSD1306.h>

void initDisplay();
void drawHUD();
void showPopup(const char *msg);
extern Adafruit_SSD1306 display;
