On Raspberry Pi OS, `dtoverlay=` entries in `/boot/config.txt` use **device tree overlays** to configure hardware behavior—this includes assigning GPIO pins special functions like shutdown, UART, I²C, etc.

Here's a **comprehensive list of common GPIO-related overlays** you can use, with descriptions and usage examples.

---

## 🔌 Common GPIO-related `dtoverlay=` Presets

| Overlay | Purpose | Default GPIO | Example |
|--------|---------|--------------|---------|
| `gpio-shutdown` | Shutdown on button press | GPIO 3 | `dtoverlay=gpio-shutdown` |
| `gpio-restart` | Reboot on button press | GPIO 3 | `dtoverlay=gpio-restart` |
| `gpio-poweroff` | Set GPIO high or low on shutdown | GPIO 26 | `dtoverlay=gpio-poweroff,gpiopin=26,active_low=1` |
| `gpio-fan` | Turn fan on/off based on temp | GPIO 14 | `dtoverlay=gpio-fan,gpiopin=14,temp=55000` |
| `gpio-key` | Emulate keypress on GPIO event | (custom) | `dtoverlay=gpio-key,gpio=17,keycode=116,label=power` |
| `i2c-gpio` | Create I²C interface on arbitrary GPIOs | GPIO 23/24 | `dtoverlay=i2c-gpio,i2c_gpio_sda=23,i2c_gpio_scl=24` |
| `spi-gpio` | Create SPI interface on arbitrary GPIOs | (custom) | `dtoverlay=spi-gpio,mosi=20,miso=19,sclk=21,cs0=18` |
| `uart-gpio` | Create UART on arbitrary GPIOs | (custom) | `dtoverlay=uart-gpio,gpio_tx=14,gpio_rx=15` |
| `pi3-act-led` | Redirect ACT LED to GPIO | GPIO 47 (Pi 3 only) | `dtoverlay=pi3-act-led,gpio=18` |
| `pi3-disable-bt` | Disable Bluetooth to free UART | - | `dtoverlay=pi3-disable-bt` |
| `pi3-miniuart-bt` | Use mini UART for BT, free full UART | - | `dtoverlay=pi3-miniuart-bt` |

---

## 🔄 Details for Key Overlays

### 🔹 `gpio-shutdown`
- Triggers **safe shutdown** when GPIO is pulled low
- Optional parameters:
  - `gpio_pin` (default: 3)
  - `active_low=1` or `0` (polarity)
  - `gpio_pull=up/down/none`

```ini
dtoverlay=gpio-shutdown,gpio_pin=17,active_low=1
```

---

### 🔹 `gpio-restart`
- Triggers **safe reboot** when GPIO is pulled low
- Default: GPIO 3
- Parameters:
  - `gpio_pin`
  - `active_low`
  - `gpio_pull`

```ini
dtoverlay=gpio-restart,gpio_pin=27
```

---

### 🔹 `gpio-poweroff`
- Drives a GPIO **high or low after halt**, useful to **cut external power**
- Optional parameters:
  - `gpiopin` (default: 26)
  - `active_low=0|1` (whether "on" is high or low)
  - `input=0|1` (input mode)
  - `export=0|1` (export to sysfs)

```ini
dtoverlay=gpio-poweroff,gpiopin=22,active_low=1
```

---

### 🔹 `gpio-fan`
- Turns a GPIO-controlled fan on/off based on temp threshold
- Parameters:
  - `gpiopin`
  - `temp` (in millidegrees C)

```ini
dtoverlay=gpio-fan,gpiopin=18,temp=60000
```

---

### 🔹 `gpio-key`
- Emulates **Linux key events** from GPIO presses
- Useful for adding volume or power buttons
- Parameters:
  - `gpio`
  - `keycode` (Linux input keycode)
  - `label` (descriptive name)

```ini
dtoverlay=gpio-key,gpio=17,keycode=116,label=power
```

---

## 📚 Discover Available Overlays

To list all available overlays on your system:
```bash
ls /boot/overlays/
```

To view available parameters for a specific overlay:
```bash
sudo dtoverlay -h gpio-shutdown
```

---

## ⚠️ Notes
- Some GPIOs are used at boot time (e.g., I²C, SPI, UART), be cautious when overriding them.
- `gpio=3` (physical pin 5) is shared with I²C SDA, so using it for `shutdown`/`restart` may conflict with I²C.
