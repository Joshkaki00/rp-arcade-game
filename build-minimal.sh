#!/bin/bash
# Ultra-minimal test - just boot and loop (no peripherals at all)

export PATH="/Users/joshkaki/.local/aarch64-toolchain/bin:$PATH"

echo "Building ultra-minimal test (boot loop only)..."

# Compile just the boot loop - no C code, no peripherals
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/boot_blink.S -o boot_blink.o

# Link just the boot code
aarch64-none-elf-ld -T linker.ld boot_blink.o -o kernel8.elf
aarch64-none-elf-objcopy kernel8.elf -O binary kernel8.img

SIZE=$(ls -lh kernel8.img | awk '{print $5}')

echo ""
echo "✓ Ultra-minimal kernel built! ($SIZE)"
echo ""
echo "This version:"
echo "  ✓ Boots the CPU"
echo "  ✓ Runs an infinite loop with delays"
echo "  ✓ Does NOT touch ANY peripherals"
echo "  ✓ Does NOT try to initialize framebuffer"
echo ""
echo "If this STILL crashes, the issue is with:"
echo "  - USB boot configuration"
echo "  - Firmware files"
echo "  - config.txt settings"
echo ""
echo "If this WORKS (doesn't crash), we know:"
echo "  ✓ Kernel loads successfully"
echo "  ✓ CPU starts executing"
echo "  ✓ The crash is from peripheral access"
echo ""
echo "Copy kernel8.img to USB. Screen will stay black but Pi should"
echo "stay powered (green LED on, fan running if you have one)."
