#!/bin/bash
# Build minimal test version for Pi 5

export PATH="/Users/joshkaki/.local/aarch64-toolchain/bin:$PATH"

echo "Building Pi 5 test kernel (framebuffer only)..."

# Compile test main
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/boot.S -o boot.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/main_test.c -o main_test.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/framebuffer.c -o framebuffer.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/mailbox.c -o mailbox.o

# Link with only framebuffer components
aarch64-none-elf-ld -T linker.ld boot.o main_test.o framebuffer.o mailbox.o -o kernel8.elf
aarch64-none-elf-objcopy kernel8.elf -O binary kernel8.img

echo ""
echo "✓ Test kernel built!"
echo ""
echo "This minimal version:"
echo "  - Only initializes framebuffer"
echo "  - Shows 7 colored horizontal bands"
echo "  - No GPIO, no timer, no game logic"
echo "  - Should NOT crash on Pi 5"
echo ""
echo "Copy to USB and test. If you see colors, framebuffer works!"
