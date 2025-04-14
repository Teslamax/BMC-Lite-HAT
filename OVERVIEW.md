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
- Pi also connected to your Mac for serial/SSH
- **Switch disables Pi 5V connection to XIAO**, preventing USB port backfeed

### 🚀 RUN Mode (Deployment)
- Pi powers the XIAO via GPIO Pin 2 through a **Schottky diode**
- USB-C is unplugged or only connected for data (not power)
- XIAO receives power only from the Pi

### ⚠️ Note:
- Never connect both USB-C and Pi 5V with the switch in the wrong position.
- A properly labeled switch position (e.g., "DEV ←→ RUN") is strongly recommended.

---

## 🔌 Power Architecture

- **V_SYS rail** is shared between Pi 5V (via diode) and optional USB power
- XIAO VBUS (Pin 14) is connected to V_SYS in RUN mode
- Schottky diode (e.g., SS14 or BAT54) protects the Pi from reverse current when USB is connected

---

## 🧱 Physical Configuration

- Board form factor: smaller than pHAT, compatible with Pi Zero GPIO headers
- GPIO header footprint supports stacking headers or through-holes only
- OLED I²C header (4-pin, with labeled address: 0x3C)
- Optional I²C GPIO expander (MCP23008 or MCP23017 footprint, unpopulated unless needed)

---

## 🔧 Prototyping Notes

- Use a solderless breadboard for initial testing
- Use long-lead tactile switches if buttons don't contact
- XIAO Pin 14 = VBUS (5V in)
- XIAO Pin 13 = GND
- UART (TX/RX), I²C (SDA/SCL), and control signals mapped in `pins.md`

---

## 🔋 Power Safety Summary

| Condition | Safe? | Notes |
|-----------|-------|-------|
| Only Pi USB connected | ✅ | Pi powers XIAO through diode |
| Only XIAO USB connected | ✅ | USB powers XIAO |
| Both connected, switch in DEV mode | ✅ | Pi 5V is disconnected from XIAO |
| Both connected, switch in RUN mode | ❌ | Risk of backfeed between USB ports |

---

## 🔢 GPIO Allocation Summary

### ✅ GPIOs Used on the XIAO RP2040

| GPIO  | Pin | Purpose                                 |
|-------|-----|-----------------------------------------|
| 0     | 1   | UART TX → Pi (GPIO15)                   |
| 1     | 2   | UART RX ← Pi (GPIO14)                   |
| 4     | 10  | I²C SDA → OLED & Expander (Addr `0x3C`, `0x20`) |
| 5     | 5   | I²C SCL → OLED & Expander               |
| 6     | 6   | Shutdown signal → Pi (GPIO17)           |
| 7     | 7   | Reboot signal → Pi (GPIO27)             |
| 8     | 8   | User-defined button → Pi (GPIO22)       |
| 9     | 9   | Ready signal ← Pi (GPIO5)               |
| 10    | 10  | Heartbeat ← Pi (GPIO6)                  |
| 26    | 1   | INT ← I²C expander                      |

> The 3 buttons (shutdown, reboot, user1) are debounced in software on the XIAO before being driven out to the Pi GPIOs. Each button uses **2 GPIOs on the XIAO** (input + gated output). The 6 total debounced outputs are handled by the I²C expander.

---

### 🟡 Reserved or Flexible GPIOs

| GPIO  | Pin | Alt Function | Suggested Use |
|-------|-----|--------------|----------------|
| 2     | 9   | SPI SCK      | Reserve for future SPI use or test/debug |
| 3     | 11  | SPI MISO     | Same as above |
| 4     | 10  | SPI MOSI     | Dual-use (currently I²C SDA) |
| 27    | 2   | —            | General GPIO (digital) |
| 28    | 3   | —            | General GPIO (ADC capable) |
| 29    | 4   | —            | General GPIO (ADC capable) |

> These 6 GPIOs are available for future functionality: SPI interface, analog sensors, additional user inputs, debug pads, or extra LEDs.

---

## 📁 File Structure

- `OVERVIEW.md` – This file
- `pins.md` – Pin mappings and signal roles
- `power.md` – Diagrams and circuit details for power sharing
- `schematic.kicad_sch` – KiCad schematic
- `pcb.kicad_pcb` – KiCad board layout

---


Let me know if you'd like a Markdown-formatted version with collapsible sections or a printable GPIO cheat sheet for your workspace!
This configuration allows safe, clear separation between development and deployment while avoiding USB damage risk. Let me know if you want an annotated power diagram or switch layout!

