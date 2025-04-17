#include "uart_parser.h"

static String lineBuf;
static bool atLineStart = true;
static const char *PREFIX = "🐧 ";  // emoji or string you like

void initUARTParser() {
  // Nothing special yet — just ensure Serial1.begin() was called in setup()
  lineBuf.reserve(128);  // avoid reallocations
}

void parseUART() {
  // 1) Read & buffer until newline
  while (Serial1.available()) {
    char c = Serial1.read();

    // Relay with prefix handling
    if (atLineStart) {
      Serial.print(PREFIX);
      atLineStart = false;
    }
    Serial.write(c);

    // Build up our line buffer (strip CR)
    if (c != '\r') {
      if (c == '\n') {
        // Process the full line
        processLine(lineBuf);
        lineBuf = "";
        atLineStart = true;
      } else {
        lineBuf += c;
      }
    }
  }

  // (Optional) handle USB→UART data if you still want two‑way bridging
  while (Serial.available()) {
    Serial1.write(Serial.read());
  }
}

// Called once per newline‑terminated line
static void processLine(const String &line) {
  // Simple substring matches — tweak to your exact console messages
  if (line.indexOf("BOOTING") >= 0) {
    setSystemState(STATE_BOOTING);
  }
  else if (line.indexOf("Running") >= 0 || line.indexOf("RUNNING") >= 0) {
    setSystemState(STATE_RUNNING);
  }
  else if (line.indexOf("Shutting down") >= 0) {
    setSystemState(STATE_SHUTTING_DOWN);
  }
  else if (line.indexOf("Halted") >= 0) {
    setSystemState(STATE_HALTED);
  }
  else if (line.indexOf("CRASH") >= 0) {
    setSystemState(STATE_CRASH);
  }
  else if (line.indexOf("unresponsive") >= 0) {
    setSystemState(STATE_UNRESPONSIVE);
  }
  // else leave the state unchanged
}
