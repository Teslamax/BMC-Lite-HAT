A minimalist GPIO-based board and firmware stack that brings essential BMC (Baseboard Management Controller)-like functionality to Raspberry Pi Zero/Zero 2 and other models. The design prioritizes intuitive LED state feedback, safe shutdown, minimal dependencies, and microcontroller-based autonomy.

---

## 🧠 Overview

**BMC-Lite HAT** is a Pi Zero-sized HAT (pHAT) powered by a microcontroller (e.g. RP2040 or ESP32), featuring:

- 🌈 A single RGB NeoPixel LED for status indication
- 🔘 One or more pushbuttons (shutdown, user-defined)
- 🔄 Serial connection to Pi UART for boot/crash detection
- 🔌 GPIO interaction via Raspberry Pi `dtoverlay`s:
  - `gpio-shutdown`
  - `gpio-poweroff`
  - `gpio-restart`
- 🔎 Optional heartbeat pin for live Pi monitoring
- 🛠️ USB-C for firmware upload, debug console, or CLI

---

## 🧱 Hardware Requirements

### 🔲 Microcontroller Options
- RP2040 (e.g., QT Py RP2040, XIAO RP2040)
- ESP32 (for Bluetooth Classic SPP support, optional)

### 🔗 Connections to Pi GPIO
| Function          | Pi GPIO | Dir.     | Description                       |
|------------------|---------|----------|-----------------------------------|
| Shutdown Trigger | GPIO22  | MCU→Pi   | `dtoverlay=gpio-shutdown`        |
| Poweroff Signal  | GPIO26  | Pi→MCU   | `dtoverlay=gpio-poweroff`        |
| Reset Trigger    | GPIO27  | MCU→Pi   | `dtoverlay=gpio-restart`         |
| Heartbeat        | GPIO17  | Pi→MCU   | Optional: toggled by systemd      |
| UART TX          | GPIO14  | Pi→MCU   | Serial console output             |
| UART RX          | GPIO15  | MCU→Pi   | Optional, for Pi commands         |
| RUN (reset pin)  | Header  | MCU→Pi   | Optional: direct reset            |

### 💡 Components
- 1x WS2812 RGB LED (NeoPixel)
- 1–2x tactile pushbuttons
- Optional: I2C OLED 128x32

### ⚡ Power Design
- MCU powered from Pi 5V GPIO rail
- Schottky diode between Pi 5V → MCU VIN to prevent USB backfeed
- USB-C used for optional debug, firmware upload

---

## 🌈 LED Status Scheme

| State            | Color   | Behavior     | Meaning                      |
|------------------|---------|--------------|-------------------------------|
| Off              | Off     | Off          | No Pi power                  |
| Booting          | Orange  | Breathing    | Parsing serial boot logs     |
| Running          | Green   | Solid        | Heartbeat OK                 |
| Shutting Down    | Yellow  | Slow Blink   | Shutdown in progress         |
| Halted           | Red     | Solid        | GPIO26 high: safe to power off|
| Crash / Panic    | Magenta | Fast Blink   | Kernel panic, log detected   |
| Unresponsive     | Amber   | 2s Blink     | Heartbeat timeout            |

---

## 📥 Input Methods

### 1. **Shutdown Button**
- Pulls GPIO22 low via MCU to initiate clean shutdown
- No software needed beyond `dtoverlay=gpio-shutdown`

### 2. **User Button**
- Can trigger user-defined actions in firmware (e.g., LED test, override, cycle states)

---

## 📤 Output & Monitoring

### 1. **UART Serial Parsing**
- Monitor `/dev/serial0` (GPIO14 TX)
- Detect system states from console output:
  - "Booting Linux...", "Reached target...", "Shutting down..."

### 2. **Heartbeat GPIO**
- Optional systemd service toggles GPIO17 every 1s
- Detects Pi liveliness via state change timeout

### 3. **Poweroff Signal**
- `dtoverlay=gpio-poweroff` sets GPIO26 HIGH at shutdown complete

### 4. **Reset Pin / GPIO**
- `dtoverlay=gpio-restart` allows MCU to reboot Pi via GPIO27
- Or use physical `RUN` pin pulse

---

## ⚙️ System Configuration (Pi Side)

### Enable UART
```ini
# /boot/config.txt
enable_uart=1

# /boot/cmdline.txt
# Ensure it contains:
console=serial0,115200
```

### Configure GPIO Overlays
```ini
# /boot/config.txt

dtoverlay=gpio-shutdown,gpio_pin=22,active_low=1,gpio_pull=up
dtoverlay=gpio-poweroff,gpiopin=26,active_low=0
dtoverlay=gpio-restart,gpio_pin=27,active_low=1
```

### (Optional) Heartbeat Service
Create `/usr/local/bin/heartbeat.py`:
```python
import RPi.GPIO as GPIO, time
GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT)
while True:
    GPIO.output(17, GPIO.HIGH)
    time.sleep(0.5)
    GPIO.output(17, GPIO.LOW)
    time.sleep(0.5)
```
Add systemd unit to run on boot.

---

## 🚧 Roadmap
- [ ] Base firmware for RP2040 with state machine
- [ ] Serial console parser
- [ ] Heartbeat monitor logic
- [ ] LED controller w/ animation
- [ ] Optional OLED info display
- [ ] Custom PCB layout for pHAT form factor
- [ ] Case design (3D printed)

---

## 📄 License
MIT or CC-BY 4.0, TBD

---

## 💬 Credits
Created by [You], with architectural guidance from ChatGPT. Inspired by real-world BMCs, IPMI, systemd, and the idea that small devices deserve good UX too.



## 💬 Credits
Created by [You], with architectural guidance from ChatGPT. Inspired by real-world BMCs, IPMI, systemd, and the idea that small devices deserve good UX too.
