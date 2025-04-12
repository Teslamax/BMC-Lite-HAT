# BMC-Lite HAT – Design Overview

**BMC-Lite HAT** is a compact, low-cost control and status interface board for headless Raspberry Pi systems.  
It provides **safe shutdown and reboot control**, **user input**, **status indication**, and **power protection**, while enabling easy prototyping and future expandability.

---

## 🎯 Project Goals

- Allow clean shutdown and reboot of headless Raspberry Pi devices
- Support up to 3 debounced physical buttons (shutdown, reboot, user)
- Monitor Pi health via UART and a heartbeat GPIO
- Provide visual feedback using the XIAO's onboard RGB LED and optional I²C OLED
- Maintain power separation and protection between the Pi and USB
- Fit entirely on a solderless breadboard for early prototyping

---

## 🧱 Hardware Overview

### MCU: **Seeed XIAO RP2040**

- Handles button input with debouncing
- Sends shutdown and reboot signals to the Pi
- Receives Pi "ready for poweroff" and "heartbeat" signals
- Optionally monitors UART output from Pi
- Drives an optional I²C OLED
- Uses all **12 GPIOs** on the XIAO

### Raspberry Pi

- Uses `dtoverlay`-based GPIO triggers
- Powered independently (no USB power sharing)
- Communicates with XIAO via GPIO and UART
- Provides power to XIAO (with diode protection)

---

## 📌 Pin Assignments (Final – All 12 GPIOs Used)

| XIAO GPIO | XIAO Label | Purpose                             | Direction | Pi GPIO | Pi Header Pin | Notes |
|-----------|------------|-------------------------------------|-----------|---------|----------------|-------|
| GPIO0     | D0         | UART TX (optional)                  | Output    | —       | —              | Not used yet |
| GPIO1     | D1         | UART RX (Pi TX, console log)        | Input     | GPIO14  | Pin 8          | Serial console |
| GPIO2     | D2         | Shutdown button                     | Input     | —       | —              | Debounced |
| GPIO3     | D3         | Reboot button                       | Input     | —       | —              | 〃 |
| GPIO4     | D4         | User-defined button                 | Input     | —       | —              | 〃 |
| GPIO5     | D5         | GPIO to Pi – shutdown trigger       | Output    | GPIO17  | Pin 11         | Connects to `gpio-shutdown` |
| GPIO6     | SDA        | I²C SDA (OLED, expander)            | I/O       | GPIO2   | Pin 3          | Shared I²C |
| GPIO7     | SCL        | I²C SCL                              | I/O       | GPIO3   | Pin 5          | 〃 |
| GPIO26    | A0         | GPIO to Pi – reboot trigger         | Output    | GPIO18  | Pin 12         | Connects to `gpio-restart` |
| GPIO27    | A1         | GPIO to Pi – user signal            | Output    | GPIO27  | Pin 13         | Custom Pi-side use |
| GPIO28    | A2         | GPIO from Pi – poweroff ready       | Input     | GPIO22  | Pin 15         | Connects to `gpio-poweroff` |
| GPIO29    | A3         | GPIO from Pi – heartbeat            | Input     | GPIO23  | Pin 16         | Connects to `gpio-heartbeat` |

> ✅ All 12 XIAO GPIOs are assigned  
> ✅ UART, I²C, input, and output roles are well-isolated  
> ⚡ GPIOs are never driven in both directions

---

## ⚡ Dual-Power Protection: Discrete Schottky Diodes

### Purpose:
Prevent power contention between **USB (VBUS)** and **Pi 3.3V rail** by OR-ing both into a common `V_SYS` rail.

### Materials:
- 2x discrete Schottky diodes (e.g., 1N5817, BAT85)
- 1x 10–47µF ceramic capacitor (0805/1206, X5R or X7R)

### Diagram:

```text
Pi 3.3V ───┬────|<|──┐
           │         │
           │         ├───► V_SYS ──► XIAO 3.3V (Pin 13)
USB 3.3V ──┴────|<|──┘
                 │
              [Capacitor]
                 │
                GND
