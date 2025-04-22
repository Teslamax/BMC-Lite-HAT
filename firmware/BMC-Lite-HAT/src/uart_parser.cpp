#include "uart_parser.h"

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "config.h"
#include "pinmap.h"
#include "debug.h"

// External display object declared in main.cpp or elsewhere
extern Adafruit_SSD1306 display;

static String piLineBuf;     // for Pi → USB parsing
static bool  piAtLineStart = true;

static String userLineBuf;   // for USB → Pi command parsing
static bool  userAtLineStart = true;
static bool  echoEnabled = ECHO_USER_INITIAL;

void initUARTParser() {
  piLineBuf.reserve(128);
  userLineBuf.reserve(128);
}

static void handleUserCommand(const String &line) {
  /*
  Serial.print("📥 Received command: '");
  Serial.print(line);
  Serial.println("'");
  */

  String cmd = line;
  cmd.trim();  // ← this removes \r or spaces accidentally typed

  if (line.equalsIgnoreCase("/echo on")) {
    echoEnabled = true;
    Serial.println("🛠 Echo enabled");
  }
  else if (line.equalsIgnoreCase("/echo off")) {
    echoEnabled = false;
    Serial.println("🛠 Echo disabled");
  }
  else if (line.startsWith("/loglevel ")) {
    int lvl = line.substring(10).toInt();
    cdcLogLevel = constrain(lvl, 0, 3);
    logInfo("Log level set to %d", cdcLogLevel);
  }
  else if (line.startsWith("/i2cscan")) {
    Serial.println("🔍 Scanning I2C...");
    for (uint8_t addr = 1; addr < 127; addr++) {
      Wire.beginTransmission(addr);
      if (Wire.endTransmission() == 0) {
        Serial.print("📟 Found device at 0x");
        Serial.println(addr, HEX);
      }
      if (addr == OLED_I2C_ADDR) {
        Serial.println("✅ Detected OLED display");
      }
    }
    Serial.println("✅ I2C scan complete.");
  }
  else if (line.startsWith("/oledtest")) {
    Serial.println("🖥 Testing OLED...");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("BMC Lite HAT"));
    display.println(F("OLED OK ✔"));
    display.display();
  }
  else if (line.startsWith("/piuarttest")) {
    Serial.println("📤 Sending test to Pi UART...");
    Serial1.println("Hello from BMC Lite HAT via UART!");
  }
  else {
    Serial.print("❓ Unknown command: ");
    Serial.println(line);
  }
}

static void processPiLine(const String &line) {
  // your existing state‑machine matching,
  // e.g. setSystemState(...) based on keywords
  // …
}

void parseUART() {
  static bool piAtLineStart = true;
  static bool userAtLineStart = true;

  if (!Serial) {
    // Optional debug over LED or UART1
    return; // bail early - no CDC
  }

  // — Pi → USB (Green LED, CDC activity) —
  while (Serial1.available()) {
    char c = Serial1.read();
    if (piAtLineStart) {
      Serial.print(PI_ECHO_PREFIX);
      piAtLineStart = false;
    }
    Serial.write(c);
    if (c == '\n') {
      processPiLine(piLineBuf);
      piLineBuf = "";
      piAtLineStart = true;
    } else if (c != '\r') {
      piLineBuf += c;
    }

    pulseLed(LED_GREEN_PIN);   // blink green on RX
    markCdcActivity();         // CDC activity (input from Pi)
  }

  // — USB → Pi (Red LED, CDC activity) —
 
  /*
    if (Serial.available() > 0) {
      Serial.println("🟦 Incoming CDC byte...");
    }
  */
    
  

 
  while (Serial.available()) {
    char c = Serial.read();
    markCdcActivity();         // CDC activity (input from host)
    pulseLed(LED_RED_PIN);     // blink red on TX

  /*
  // DEBUG: show every character
  Serial.print("🔸 Read: '");
  Serial.print(c);
  Serial.print("' (");
  Serial.print((int)c);  // ASCII code
  Serial.println(")");
  */

    if (userAtLineStart) {
      userLineBuf = "";
      userAtLineStart = false;
    }
    userLineBuf += c;

    if (c == '\n' || c == '\r') {
      userLineBuf.trim();  // ← very important to clean \r etc

/*
      Serial.print("📥 Full command: ");
      Serial.println(userLineBuf);
*/  
      if (echoEnabled) {
        Serial.print(ECHO_USER_PREFIX);
        Serial.println(userLineBuf);  // echo the full line
      }

      handleUserCommand(userLineBuf); // parse after echoing

      userAtLineStart = true;
    } else if (echoEnabled && userAtLineStart) {
      Serial.print(ECHO_USER_PREFIX);
    }

    Serial1.write(c);
  }
}


void initSerialInterfaces() {
  Serial.begin(115200);       // USB‑CDC
  while (!Serial);            // wait for connection

  delay(200);
  Serial.println("🟦 USB CDC ready");  // Always confirm this in setup()
  logInfo("Starting BMC Lite HAT firmware v%s", FIRMWARE_VERSION);
  
  // Pi UART
  Serial1.setTimeout(UART1_TIMEOUT_MS);   // optional, for read timeouts if needed
  Serial1.begin(UART1_BAUDRATE, UART1_PARITY);
  Serial1.println("📤 UART1- Pi UART initialized at " + String(UART1_BAUDRATE) + " baud");
  Serial.println("🛠 Serial interfaces ready");
}

void pulseLed(uint8_t pin) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(2000);  // ~2ms pulse
  digitalWrite(pin, LOW);
} 

void markCdcActivity() {
  static unsigned long lastCdc = 0;
  static bool cdcOn = false;

  lastCdc = millis();
  if (!cdcOn) {
    digitalWrite(LED_BLUE_PIN, HIGH);
    cdcOn = true;
  }

  // Schedule shutdown of LED later
  static unsigned long* lastPtr = &lastCdc;
  static bool* cdcFlag = &cdcOn;

  static struct {
    void update() {
      if (*cdcFlag && millis() - *lastPtr > 200) {
        digitalWrite(LED_BLUE_PIN, LOW);
        *cdcFlag = false;
      }
    }
  } ledController;

  ledController.update();
}
