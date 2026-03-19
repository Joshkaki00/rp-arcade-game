#!/bin/bash
# Build white screen test for Pi 4

export PATH="/Users/joshkaki/.local/aarch64-toolchain/bin:$PATH"

echo "Building white screen test for Pi 4..."

aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/boot.S -o boot.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/main_white.c -o main_white.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/mailbox.c -o mailbox.o

aarch64-none-elf-ld -T linker.ld boot.o main_white.o mailbox.o -o kernel8.elf
aarch64-none-elf-objcopy kernel8.elf -O binary kernel8.img

echo ""
echo "✓ White screen test built!"
echo ""
echo "This will:"
echo "  1. Initialize framebuffer via mailbox"
echo "  2. Fill ENTIRE screen with WHITE (0xFFFFFF)"
echo "  3. If you see white, framebuffer works!"
echo "  4. If black, either:"
echo "     - Wrong HDMI port (try both!)"
echo "     - Monitor doesn't support 1280x720"
echo "     - Mailbox call failed"
echo ""
echo "Copy to USB/SD and test on Pi 4."
