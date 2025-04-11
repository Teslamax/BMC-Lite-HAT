# BMC-Lite-HAT System Wiring & Schematic (XIAO RP2040)

## 📦 Components

- 1x **Seeed Studio XIAO RP2040** (USB-C, onboard RGB LED — used)
- 1x **2×7 or 2×8 low-profile SMD female header** (for socketing XIAO)
- 4x Momentary Pushbuttons
- 4x 10kΩ resistors (external pull-ups or optional)
- 4x 0.1µF ceramic capacitors (button debounce)
- 1x 1N5819 Schottky Diode (Pi 5V → XIAO VIN, backfeed prevention)
- 1x 1N5819 Schottky Diode (XIAO VIN → Pi 5V, reverse backfeed)
- 1x 100 µF electrolytic capacitor (power smoothing)
- 2x resistors (10kΩ + 4.7kΩ) for voltage divider (Pi 5V sense)
- Jumper wires / headers / breadboard
- (Optional) I²C OLED or expander module on shared I²C bus (GPIOs 4/5 unused if onboard RGB LED is retained)

---

## 🧭 Raspberry Pi GPIO Assignments

| Function            | Pi Pin # | BCM GPIO | Direction | Description                                  |
|---------------------|----------|----------|-----------|----------------------------------------------|
| Shutdown Trigger    | 15       | GPIO22   | Input     | Pi shuts down when pulled LOW by MCU         |
| Poweroff Indicator  | 37       | GPIO26   | Output    | Pi drives HIGH when safe to power off        |
| Reset Trigger       | 13       | GPIO27   | Input     | Pi reboots when pulled LOW by MCU            |
| UART TX (Pi → MCU)  | 8        | GPIO14   | Output    | Serial console output from Pi                |
| Heartbeat GPIO      | 11       | GPIO17   | Output    | Pi toggles HIGH/LOW to indicate activity     |

---

## 🧭 GPIO Assignments (XIAO RP2040)

| Function            | XIAO Pin | RP2040 GPIO | Notes                             |
|---------------------|----------|-------------|-----------------------------------|
| Shutdown Button     | D0       | GPIO0       | Input from physical button        |
| Reboot Button       | D1       | GPIO1       | Input from physical button        |
| User Button 1       | D2       | GPIO2       | Optional `gpio-key`               |
| RGB LED             | —        | GPIO3/4/5   | Onboard RGB LED (PWM control)     |
| 5V Sense Input      | —        | GPIO6       | From Pi 5V via voltage divider    |
| Poweroff Status     | D4       | GPIO7       | Input from Pi GPIO26              |
| Shutdown Trigger    | D5       | GPIO8       | Output to Pi GPIO22               |
| Restart Trigger     | D6       | GPIO9       | Output to Pi GPIO27               |
| Heartbeat Monitor   | D7       | GPIO10      | Input from Pi GPIO17              |
| UART RX (Pi TX)     | D8       | GPIO11      | Serial input from Pi GPIO14       |

Note: The onboard RGB LED is retained for system status indication. A standalone NeoPixel is **not used**, but can be considered for future revisions if brightness or positioning becomes a concern.

The XIAO RP2040 is socketed using low-profile **SMD female headers** to allow replacement or upgrade while keeping the main PCB reflow-friendly.

---

## 🔌 Power Wiring

- **Pi 5V GPIO** → 1N5819 diode → XIAO VIN
- **XIAO VIN** → 1N5819 diode → Pi 5V GPIO *(optional, only if Pi may be powered from XIAO)*
- **XIAO GND** ↔ **Pi GND** (shared ground)
- 100 µF electrolytic capacitor across VIN and GND on XIAO

---

## 🔋 Voltage Divider (5V Sense)

- R1 = 10kΩ (Pi 5V to XIAO GPIO6)
- R2 = 4.7kΩ (XIAO GPIO6 to GND)
- Output voltage ≈ 3.2V when Pi is powered

---

## 🔘 Button Wiring

### Button 1: Shutdown
- Between GPIO0 and GND
- Internal pull-up or 10kΩ to 3.3V
- 0.1 µF capacitor across GPIO0 and GND

### Button 2: Reboot
- Between GPIO1 and GND
- Same resistor and debounce setup as above

### Button 3: User-defined / gpio-key
- Between GPIO2 and GND
- Optional `gpio-key` or manual override/test

### Button 4: Optional second user button (analog read or I²C expander required)

---

## 🔁 Pi GPIO Overlay Config

In `/boot/config.txt`:

```ini
dtoverlay=gpio-shutdown,gpio_pin=22,active_low=1,gpio_pull=up
dtoverlay=gpio-poweroff,gpiopin=26,active_low=0
dtoverlay=gpio-restart,gpio_pin=27,active_low=1
dtoverlay=gpio-key,gpio=23,keycode=103,label="userbtn"
enable_uart=1
```

Also:
- GPIO14 = Pi TX → XIAO RX (UART debug stream)
- GPIO17 = Heartbeat pulse from systemd script

---

## 🧪 Debugging

Use USB-C for:
- Power during programming
- CDC Serial debug logs
- Optional CLI interface over USB serial

---

## 💡 LED Status

- Onboard RGB LED (GPIO3/4/5)
- PWM-controlled with software blending and animation
- Fully used for state indication (booting, running, halted, crash, etc.)
- No external NeoPixel required for single-LED feedback

---

Let me know if you’d like this visualized in Fritzing or converted to KiCad for schematic + PCB layout!

