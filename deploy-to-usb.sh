#!/bin/bash
# Copy files to USB drive mounted at /Volumes/BOOT

BOOT_DIR="/Volumes/BOOT"
FILES="bootcode.bin start4.elf fixup4.dat config.txt kernel8.img"

if [ ! -d "$BOOT_DIR" ]; then
    echo "Error: USB drive not found at $BOOT_DIR"
    echo "Please format a USB drive as FAT32 and mount it"
    echo ""
    echo "On macOS:"
    echo "  1. Insert USB drive"
    echo "  2. Open Disk Utility"
    echo "  3. Select the USB drive"
    echo "  4. Click 'Erase'"
    echo "  5. Format: MS-DOS (FAT32)"
    echo "  6. Name: BOOT"
    echo "  7. Click 'Erase'"
    exit 1
fi

echo "Copying files to $BOOT_DIR..."

for file in $FILES; do
    if [ -f "$file" ]; then
        cp "$file" "$BOOT_DIR/"
        echo "  ✓ $file"
    else
        echo "  ✗ $file (not found)"
    fi
done

echo ""
echo "✓ Files copied to USB drive!"
echo ""
echo "You can now:"
echo "  1. Eject the USB drive"
echo "  2. Insert into Raspberry Pi"
echo "  3. Power on and enjoy!"
