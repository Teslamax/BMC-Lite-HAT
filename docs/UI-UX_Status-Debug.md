## BMC Lite HAT Status & Debug Interface

This document describes the three primary status/debug channels on the BMC Lite HAT: **USB‑CDC (Serial)**, **On‑Board SSD1306 OLED**, and **Discrete R/G/B LEDs**, along with the logging levels, UI/UX conventions, and console commands available to developers and end‑users.

---

### 1. USB‑CDC (Serial) Channel

#### Purpose
- Full‑verbosity logging for development and field diagnostics.
- Command interface for runtime configuration (e.g. log levels, echo control).

#### Logging Levels & Prefixes
| Level      | Macro        | Prefix  | Description                       |
|------------|--------------|---------|-----------------------------------|
| Error      | `logError`   | ❌       | Fatal errors — halt or recoverable |
| Warn       | `logWarn`    | ⚠️       | Warnings — recoverable issues      |
| Info       | `logInfo`    | ℹ️       | General status updates            |
| Verbose    | `logVerbose` | 🔍       | Detailed debug / trace messages   |

- **Runtime level** controlled by `cdcLogLevel` (0–3).
- **Change** via console:
  ```
  /loglevel <0|1|2|3>   # set verbosity
  ```

#### Console Commands
- `/echo on` / `/echo off`  → enable/disable per‑line user echo
- `/loglevel N`             → set CDC verbosity (0=errors…3=all)
- Custom: `/i2cscan`, `/showheap`, `/reset`

#### Firmware Echo & Pi‑UART Relay
- **Firmware Echo**: Compile‑time default controlled by `ECHO_USER_INITIAL`, and runtime toggled with `/echo on` and `/echo off`. When enabled, every user‑entered line is echoed back over CDC prefixed with `ECHO_USER_PREFIX` (e.g. "➡️ ").  
- **Pi UART Relay**: All lines received from the Pi’s UART (`Serial1`) are forwarded over USB‑CDC and prefixed with `PI_ECHO_PREFIX` (e.g. "🐧 ") to distinguish Pi‑originated messages from firmware logs.
- `/echo on` / `/echo off`  → enable/disable per‑line user echo
- `/loglevel N`             → set CDC verbosity (0=errors…3=all)
- Custom: `/i2cscan`, `/showheap`, `/reset`

---

### 2. On‑Board SSD1306 OLED (Blue)

#### Purpose
- Contextual, menu‑driven status display.
- Transient pop‑ups for errors or user actions.

#### UI Layout
```
╔════════════════════════╗
║ State: <STATE_NAME>    ║  ← line 1: current system state
║ Last Cmd: <text…>      ║  ← line 2: last console command
║ I2C: 0x3C,0x20 OK      ║  ← line 3: bus health
║ Uptime: 12s | Heap: 42K║  ← line 4: stats
╚════════════════════════╝
```

- **Transient Alerts:** overlay full screen for 1–2 s on errors.
- **Menu Mode:** use `USER1`/`SHUTDOWN` as up/down, `REBOOT` as Enter:
  ```
  • LogLevel: 2
    I2C Scan
    Reboot
  ```

---

### 3. Discrete R/G/B LEDs (GP17, GP16, GP25)

#### Purpose
- Immediate, glanceable indicators of bus & console activity.

| LED     | Pin   | Function                | Behavior                                                         |
|---------|-------|-------------------------|------------------------------------------------------------------|
| Red     | GP17  | USB‑CDC → Pi (TX)       | 2 ms pulse on each byte sent from PC to Pi                      |
| Green   | GP16  | Pi → USB‑CDC (RX)       | 2 ms pulse on each byte received from Pi                        |
| Blue    | GP25  | CDC / I2C idle/active   | Soft blink while any activity present; OFF when idle            |

- **Pulse Width:** ~2 ms (adjustable)
- **Blink Rate:** ~200 ms toggle to indicate continuous activity

---

### Integration in `parseUART()`
```cpp
void parseUART() {
  // Pi→USB (Green)
  while (Serial1.available()) {
    pulseLED(LED_GREEN_PIN);
    // relay + prefix…
  }
  // USB→Pi (Red)
  while (Serial.available()) {
    pulseLED(LED_RED_PIN);
    // forward + optional echo…
  }
  // Activity LED (Blue)
  updateActivityLED();
}
```

---

### Summary of Console GUI/UX
1. **Verbose development:** monitor CDC at max log level with Serial Monitor.
2. **Glance diagnostics:** built‑in RGB LED shows real‑time bus & console traffic.
3. **Contextual info:** OLED offers state, metrics, and a simple menu for configuration.
4. **Commands:** `/echo`, `/loglevel`, plus custom utilities (`/i2cscan`, `/heap`, `/reboot`).

By combining these channels, you gain layered visibility: **complete logs** on CDC, **one‑look** status on LEDs, and **context menus** on the OLED, ensuring both rapid development and clear end‑user feedback.

