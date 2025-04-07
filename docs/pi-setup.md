# Raspberry Pi Setup Guide for BMC-Lite-HAT

This guide walks you through setting up your Raspberry Pi to work with the BMC-Lite HAT using GPIO overlays, UART, and the optional heartbeat monitoring service.

---

## 🧰 Files Included

- `config.txt.snippet`: Additions to your Pi's `/boot/config.txt`
- `cmdline.txt.snippet`: Serial console enable line for `/boot/cmdline.txt`
- `heartbeat.py`: Python script to toggle a GPIO as a heartbeat signal
- `heartbeat.service`: systemd unit file to run `heartbeat.py` at boot

---

## ⚙️ Step-by-Step Setup

### 1. Enable UART and Overlays

Edit your `/boot/config.txt`:

```bash
sudo nano /boot/config.txt
```

Append the following (or copy from `config.txt.snippet`):

```ini
enable_uart=1
dtoverlay=gpio-shutdown,gpio_pin=22,active_low=1,gpio_pull=up
dtoverlay=gpio-poweroff,gpiopin=26,active_low=0
dtoverlay=gpio-restart,gpio_pin=27,active_low=1
```

### 2. Enable Serial Console Output

Edit `/boot/cmdline.txt` (this file is a **single line**!):

```bash
sudo nano /boot/cmdline.txt
```

Add this to the end (if not present):

```
console=serial0,115200
```

> ⚠️ Do not break the line into multiple lines.

---

### 3. Install Heartbeat Service (Optional)

#### Copy files to their locations:

```bash
sudo cp pi-config/heartbeat/heartbeat.py /usr/local/bin/
sudo chmod +x /usr/local/bin/heartbeat.py
```

```bash
sudo cp pi-config/heartbeat/heartbeat.service /etc/systemd/system/
```

#### Enable the service:

```bash
sudo systemctl daemon-reexec
sudo systemctl enable heartbeat.service
sudo systemctl start heartbeat.service
```

To check status:

```bash
sudo systemctl status heartbeat.service
```

---

## 🔁 Reboot

After all steps are complete:

```bash
sudo reboot
```

Your Raspberry Pi should now:
- Output logs via UART
- Respond to shutdown/restart GPIOs
- Pulse GPIO17 as a heartbeat indicator

---

## ✅ Summary

- UART and overlays allow microcontroller monitoring and control
- Heartbeat helps detect unresponsive Pi
- No kernel modules or packages are required — just Python and systemd

