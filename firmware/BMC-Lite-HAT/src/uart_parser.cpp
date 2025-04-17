#include "uart_parser.h"

static String piLineBuf;     // for Pi → USB parsing
static bool  piAtLineStart = true;

static String userLineBuf;   // for USB → Pi command parsing
static bool  userAtLineStart = true;
static bool  echoEnabled = ECHO_USER_INITIAL;

void initUARTParser() {
  piLineBuf.reserve(128);
  userLineBuf.reserve(128);
}

// Helper to match and handle “/echo on” or “/echo off”
static void handleUserCommand(const String &line) {
  if (line.equalsIgnoreCase("/echo on")) {
    echoEnabled = true;
    Serial.println( "🛠 Echo enabled");
  } else if (line.equalsIgnoreCase("/echo off")) {
    echoEnabled = false;
    Serial.println("🛠 Echo disabled");
  } else if (line.startsWith("/loglevel ")) {
    int lvl = line.substring(10).toInt();
    cdcLogLevel = constrain(lvl, 0, 3);
    logInfo("Log level set to %d", cdcLogLevel);
  }
  
}

static void processPiLine(const String &line) {
  // your existing state‑machine matching,
  // e.g. setSystemState(...) based on keywords
  // …
}

void parseUART() {
  // — UART (Pi) → USB (PC) with PI_ECHO_PREFIX per line —
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
  }

  // — USB (you) → UART (Pi) *and* optional ECHO_USER_PREFIX per line —
  while (Serial.available()) {
    char c = Serial.read();

    // start buffering a new user line
    if (userAtLineStart) {
      userLineBuf = "";
      userAtLineStart = false;
    }
    userLineBuf += c;

    if (c == '\n') {
      // at end of line: handle any user commands
      handleUserCommand(userLineBuf);

      // if echo is enabled, print the prefix + the full line
      if (echoEnabled) {
        Serial.print(ECHO_USER_PREFIX);
        Serial.print(userLineBuf);
      }

      userAtLineStart = true;
    } else if (echoEnabled && userAtLineStart) {
      // If you wanted a prefix at the very first character
      Serial.print(ECHO_USER_PREFIX);
    }

    // always forward to the Pi
    Serial1.write(c);
  }
}
