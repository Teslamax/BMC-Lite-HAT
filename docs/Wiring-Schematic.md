# BMC-Lite-HAT System Wiring & Schematic (XIAO RP2040)

## 📦 Components

- 1x **Seeed Studio XIAO RP2040** (USB-C, onboard RGB LED — used)
- 1x **2×7 low-profile SMD female header** (for socketing XIAO)
- 3x Momentary Pushbuttons (`SHUTDOWN`,`REBOOT`,`USER1`)
- 1x 1N5819 Schottky Diode (Pi 5V → XIAO VIN, backfeed prevention)
- 1x 100 µF electrolytic capacitor (power smoothing)
- I²C expander (MCP23017 while breadboard prototyping)
- Jumper wires / headers / breadboard
- (Optional) I²C OLED
- **Bidirectional UART** between Pi and XIAO (GPIO14 TX and GPIO15 RX)

---

## 📦 Phase 2 Considerations (Planned BMC Features)

In future firmware and hardware expansions, BMC-Lite will evolve beyond passive monitoring to support **active Pi control** and additional diagnostics. The following features are targeted for Phase 2:

- **USB CDC** used exclusively for XIAO debug, control, and programming
- **Optional I²C OLED display** for UI output

To support this, the RGB LED GPIOs (GPIO3/4/5) may be reclaimed, and I²C devices used for expanded capability.

---

## 🧭 Raspberry Pi GPIO Assignments

| Function            | Pi Pin # | BCM GPIO | Direction | Description                                  |
|---------------------|----------|----------|:---------:|----------------------------------------------|
| UART `TX` (Pi → MCU)  | 8        | `GPIO14`   | Output    | Serial console output from Pi                |
| UART `RX` (Pi ← MCU)  | 10       | `GPIO15`   | Input     | Optional command or logging input to Pi      |
| Heartbeat GPIO      | 11       | `GPIO17`   | Output    | Pi toggles HIGH/LOW to indicate activity     |
| Reset Trigger       | 13       | `GPIO27`   | Input     | Pi reboots when pulled LOW by MCU            |
| Shutdown Trigger    | 15       | `GPIO22`   | Input     | Pi shuts down when pulled LOW by MCU         |
| Poweroff Indicator  | 37       | `GPIO26`   | Output    | Pi drives HIGH when safe to power off        |

---

## 🧭 XIAO-RP2040 GPIO Assignments

| Function            | Pin | Label | Notes                             |
|---------------------|----------|-------------|-----------------------------------|
| I²C expander interrupt | 1 - `INT` | `GPIO26` | | |
| RGB LED             | —        | GPIO3/4/5   | Onboard RGB LED |
| UART `TX` (MCU → Pi)     | 7        | `GPIO0`/`TX`      | Optional command or logging input to Pi   |
| UART `RX` (MCU ← Pi)     | 8       | `GPIO1`/`RX`      | Serial console input from Pi GPIO14       |
| I²C data | 5 | `SDA` | I²C - data | I²C data |
| I²C clock | 6 | `SCL` | I²C - clock | I²C clock |

Note: The onboard RGB LED is retained for system status indication unless repurposed to free GPIOs. USB-C remains the exclusive debug/programming interface.

The XIAO RP2040 is socketed using low-profile **SMD female headers** to allow replacement or upgrade while keeping the main PCB reflow-friendly.

---

## 🧭 GPIO Assignments (MCP23017)

| Function            | Pin      | Label       | Notes                             |
|---------------------|----------|-------------|-----------------------------------|
| I²C clock | 12 | `SCL` | I²C - clock | I²C clock |
| I²C data | 13 | `SDA` | I²C - data | I²C data |
| Poweroff Status     | 21       | `GPA0`      | Input from Pi `GPIO26`            |
| Shutdown Trigger    | 22       | `GPA1`      |  Output to Pi `GPIO22`            |
| Restart Trigger     | 23       | `GPA2`      |  Output to Pi `GPIO27`            |
| Heartbeat Monitor   | 24       | `GPA3`      | Input from Pi `GPIO17`            |
| Heartbeat Monitor   | 25       | `GPA4`      | Input from Pi `GPIO17`            |
| Heartbeat Monitor   | 26       | `GPA5`      | Input from Pi `GPIO17`            |
| Heartbeat Monitor   | 27       | `GPA6`      | Input from Pi `GPIO17`            |
| Heartbeat Monitor   | 28       | `GPA7`      | Input from Pi `GPIO17`            |


---

## 🔌 Power Wiring

- **Pi 5V GPIO** → 1N5819 diode → XIAO VIN
- **XIAO GND** ↔ **Pi GND** (shared ground)
- 100 µF electrolytic capacitor across VIN and GND on XIAO

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
- GPIO15 = XIAO TX → Pi RX (future BMC interaction)
- GPIO17 = Heartbeat pulse from systemd script

---

## 🧪 Debugging

USB-C is used on all versions of this project for:
- Power during programming
- CDC Serial debug logs
- Optional CLI interface over USB serial
- Firmware upload, runtime state control

---

## 💡 LED Status

### Silkscreen Info
This board should include the following on the silkscreen:
- **"BMC-Lite HAT"** as the board name (or stylized variant)
- **"Teslamax"** as the author or GitHub handle
- **Version identifier space** such as `Rev: ___` to be manually filled or incremented


- Onboard RGB LED (GPIO3/4/5)
- PWM-controlled with software blending and animation
- Fully used for state indication (booting, running, halted, crash, etc.)
- May be replaced in Phase 2 if GPIOs are needed

---

Let me know if you’d like this visualized in Fritzing or converted to KiCad for schematic + PCB layout!

