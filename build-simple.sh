#!/bin/bash
export PATH="/Users/joshkaki/.local/aarch64-toolchain/bin:$PATH"

echo "Building simple game (no GPIO, no timer)..."

aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/boot.S -o boot.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/main_simple.c -o main_simple.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/framebuffer.c -o framebuffer.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/mailbox.c -o mailbox.o

aarch64-none-elf-ld -T linker.ld boot.o main_simple.o framebuffer.o mailbox.o -o kernel8.elf
aarch64-none-elf-objcopy kernel8.elf -O binary kernel8.img

echo ""
echo "✓ Simple game built!"
echo ""
echo "This version:"
echo "  ✓ No GPIO (no input)"
echo "  ✓ No timer (software delay)"
echo "  ✓ Green player at bottom (static)"
echo "  ✓ Red enemy falling from top (animated!)"
echo ""
echo "If you see animation, the game works!"
echo "The hang was from GPIO/timer access."
