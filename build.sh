#!/bin/bash
# Build script that automatically uses the correct toolchain PATH

export PATH="/Users/joshkaki/.local/aarch64-toolchain/bin:$PATH"

echo "Building bare-metal Raspberry Pi arcade game..."
make "$@"

if [ -f kernel8.img ]; then
    echo ""
    echo "✓ Build successful!"
    echo "  kernel8.img is ready"
    echo ""
    echo "Next steps:"
    echo "  1. Download firmware files: ./download-firmware.sh"
    echo "  2. Copy to FAT32 USB drive:"
    echo "     - bootcode.bin"
    echo "     - start4.elf" 
    echo "     - fixup4.dat"
    echo "     - config.txt"
    echo "     - kernel8.img"
    echo "  3. Boot your Raspberry Pi from USB!"
fi
