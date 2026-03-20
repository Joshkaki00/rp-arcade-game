#!/bin/bash
export PATH="/Users/joshkaki/.local/aarch64-toolchain/bin:$PATH"

echo "Building instant-enemy version..."

aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/boot.S -o boot.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/main_instant.c -o main_instant.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/framebuffer.c -o framebuffer.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/mailbox.c -o mailbox.o

aarch64-none-elf-ld -T linker.ld boot.o main_instant.o framebuffer.o mailbox.o -o kernel8.elf
aarch64-none-elf-objcopy kernel8.elf -O binary kernel8.img

echo ""
echo "✓ Instant enemy version!"
echo ""
echo "This spawns 5 RED enemies IMMEDIATELY:"
echo "  - All 5 visible from the start"
echo "  - All moving down"
echo "  - All respawn at top"
echo ""
echo "If you STILL only see green, something else is wrong!"
