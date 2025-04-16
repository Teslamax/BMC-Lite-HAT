# BMC-Lite HAT Project Overview

A compact, GPIO-enhancing companion board designed for headless Raspberry Pi systems, especially the Pi Zero form factor. The board is based around the **Seeed XIAO RP2040** and provides button input handling, system state indication, safe power interaction, and debugging capabilities.

---

## ✅ Key Features

- Built-in XIAO RP2040 microcontroller (preassembled)
- Shutdown, reboot, and user-configurable buttons
- RGB status LED (uses onboard XIAO RGB LED)
- UART communication with Pi (for Pi serial console parsing or USB CDC passthrough)
- Optional OLED display via I²C header
- Pi GPIO signal input/output (heartbeat, poweroff-ready, etc.)
- Debounced button handling (software or via optional I²C GPIO expander)
- Power protection using Schottky diodes to prevent backfeed between Pi and USB
- **Development/Deployment switch** for safe power source management

---

## 🧠 Development vs Deployment Mode

To safely support debugging over USB while also allowing Pi-powered deployment, a **physical SPDT switch** (or jumper header) is used to select between power sources:

### 🛠 DEV Mode (Debugging)
- XIAO RP2040 is powered via USB-C from your Mac/PC
- Pi also connected to your Mac for serial/SSH/power (Pi Zero 2)
- **Switch disables Pi 5V connection to XIAO**, preventing USB port backfeed

### 🚀 RUN Mode (Deployment)
- Pi powers the XIAO via GPIO Pin 2 through a **Schottky diode**
- USB-C is unplugged or only connected for data (not power)
- XIAO receives power only from the Pi

### ⚠️ Note:
- Never connect both USB-C and Pi 5V with the switch in the wrong position.
- A properly labeled switch position (e.g., "`DEV` ←→ `RUN`") is strongly recommended.

---

## 🔋 Power Architecture

- **V_SYS rail** is shared between Pi 5V (via diode) and optional USB power
- XIAO VBUS (Pin 14) is connected to V_SYS in `RUN` mode (switch `SW1_XIAO-POWER-ISOLATION` is closed)
- Schottky diode (e.g., SS14 or BAT54) protects the Pi from reverse current when USB is connected

---

## 🧱 Physical Configuration

- Board form factor: pHAT or smaller if possible, compatible with Pi Zero GPIO headers
- GPIO header footprint supports stacking headers or through-holes only
- OLED I²C header (4-pin, with labeled address: `0x3C`)
- I²C GPIO expander (MCP23008 or MCP23017 footprint,, with labeled address: `0x20`)

---

## 📡 Heartbeat Signal Configuration

To indicate that the Pi is alive and Linux is running, a pulsed heartbeat signal is sent to the XIAO:

### 🫀 Enable Heartbeat via `config.txt`

Add this to `/boot/config.txt` on the Pi:

```ini
dtoverlay=gpio-led,gpio=6,trigger=heartbeat
```

- This configures **RPI GPIO6 (Pin 31)** to pulse at ~1Hz automatically
- Signal starts early in boot and requires no additional software
- Connect **RPI GPIO6** to **I2C Expander-MCP23008 GPIO7 (Pin 19)** to monitor

---

## 🔢 GPIO Allocation Summary

### ✅ GPIOs Used on the XIAO RP2040

| GPIO  | Pin | Purpose                                     |
|-------|-----|---------------------------------------------|
| 26    | 1   | INT ← I²C expander                          |
| 6     | 5   | I²C SDA → OLED & Expander (Addr `0x3C`, `0x20`) |
| 7     | 6   | I²C SCL → OLED & Expander                   |
| 0     | 7   | UART TX → Pi (GPIO15)                       |
| 1     | 8   | UART RX ← Pi (GPIO14)                       |

---

### 🟡 Reserved or Flexible GPIOs on the XIAO RP2040

| GPIO  | Pin | Alt Function | Suggested Use                          |
|-------|-----|--------------|----------------------------------------|
| 27    | 2   | ADC1         | General GPIO (ADC capable)             |
| 28    | 3   | ADC2         | General GPIO (ADC capable)             |
| 29    | 4   | ADC3         | General GPIO (ADC capable)             |
| 2     | 9   | SPI SCK      | Reserve for future SPI use or test/debug |
| 4     | 10  | SPI MISO     | Same as above                          |
| 3     | 11  | SPI MOSI     | Same as above                          |

> These 6 GPIOs are available for future functionality: SPI interface, analog sensors, additional user inputs, debug pads, or extra LEDs.

### ✅ GPIOs Used on the I²C expander (MCP23008)

| GPIO  | Pin | Purpose                           | IN/OUT  |
|-------|-----|-----------------------------------|---------|
|   0   |  12 | SHUTDOWN debounced                | OUT     |
|   1   |  13 | SHUTDOWN button                   | IN      |
|   2   |  14 | REBOOT debounced                  | OUT     |
|   3   |  15 | REBOOT button                     | IN      |
|   4   |  16 | USER1 debounced                   | OUT     |
|   5   |  17 | USER1 button                      | IN      |
|   6   |  18 | RDY_SHUTDOWN                      | IN      |
|   7   |  19 | HEARTBEAT                         | IN      |

> The 3 buttons (shutdown, reboot, user1) are debounced in software on the XIAO before being driven out to the Pi GPIOs. Each button uses **2 GPIOs on the I²C expander** (input + gated output). The 6 total debounced outputs are handled by the I²C expander.

---

## 🔐 Power Safety Summary

| Condition                     | Safe? | Notes                                             |
|------------------------------|-------|---------------------------------------------------|
| Only Pi USB connected        | ✅    | Pi powers XIAO through diode                     |
| Only XIAO USB connected      | ✅    | USB powers XIAO                                  |
| Both connected, switch = DEV | ✅    | Pi 5V is disconnected from XIAO                  |
| Both connected, switch = RUN | ❌    | Risk of backfeed between USB ports               |

---

## 📁 File Structure

| File                | Description                              |
|---------------------|------------------------------------------|
| `OVERVIEW.md`       | Project overview and hardware architecture |
| `pins.md`           | Detailed pin mapping and overlays         |
| `power.md`          | Power path diagrams and safety notes      |
| `schematic.kicad_sch` | Main KiCad schematic file                |
| `pcb.kicad_pcb`     | PCB layout for KiCad                      |

---

## 📌 Quick Reference

| Component         | Platform       | Notes                                     |
|------------------|----------------|-------------------------------------------|
| MCU              | XIAO RP2040    | Pre-soldered to board                     |
| Host             | Raspberry Pi   | GPIO-linked, not USB-connected            |
| Power Switch     | DEV / RUN      | Slide or jumper select                    |
| I²C OLED Address | `0x3C`         | XIAO-only I²C                             |
| I²C Expander Addr| `0x20`         | MCP23008 or MCP23017                      |
| UART             | TX/RX to Pi    | Used optionally for Pi console passthrough |
