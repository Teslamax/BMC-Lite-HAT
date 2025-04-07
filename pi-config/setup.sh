#!/bin/bash
# setup.sh - Configure Raspberry Pi for BMC-Lite-HAT functionality

set -e

echo "🔧 Starting BMC-Lite-HAT setup..."

# Copy heartbeat script
echo "📁 Installing heartbeat.py to /usr/local/bin/"
sudo cp heartbeat/heartbeat.py /usr/local/bin/
sudo chmod +x /usr/local/bin/heartbeat.py

# Install systemd unit
echo "📁 Installing heartbeat.service to /etc/systemd/system/"
sudo cp heartbeat/heartbeat.service /etc/systemd/system/
sudo systemctl daemon-reexec
sudo systemctl enable heartbeat.service
sudo systemctl start heartbeat.service

# Suggest config.txt and cmdline.txt edits
echo "⚠️ Please manually edit the following files to add overlays and UART:"
echo "  - /boot/config.txt → see pi-config/config.txt.snippet"
echo "  - /boot/cmdline.txt → see pi-config/cmdline.txt.snippet"
echo ""
echo "✅ Setup complete. Reboot to apply changes."
