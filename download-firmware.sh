#!/bin/bash
# Download Raspberry Pi firmware files needed to boot

echo "Downloading Raspberry Pi firmware files..."

FIRMWARE_BASE="https://github.com/raspberrypi/firmware/raw/master/boot"

curl -L -O "${FIRMWARE_BASE}/bootcode.bin"
curl -L -O "${FIRMWARE_BASE}/start4.elf"
curl -L -O "${FIRMWARE_BASE}/fixup4.dat"

echo ""
echo "✓ Firmware files downloaded!"
echo ""
echo "Files ready for USB drive:"
ls -lh bootcode.bin start4.elf fixup4.dat config.txt kernel8.img 2>/dev/null || true
echo ""
echo "Copy all these files to the root of a FAT32-formatted USB drive"
