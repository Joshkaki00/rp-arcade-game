#!/bin/bash
export PATH="/Users/joshkaki/.local/aarch64-toolchain/bin:$PATH"

echo "Building debug version..."

aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/boot.S -o boot.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/main_debug.c -o main_debug.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/framebuffer.c -o framebuffer.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/mailbox.c -o mailbox.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/gpio.c -o gpio.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/timer.c -o timer.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/game.c -o game.o

aarch64-none-elf-ld -T linker.ld boot.o main_debug.o framebuffer.o mailbox.o gpio.o timer.o game.o -o kernel8.elf
aarch64-none-elf-objcopy kernel8.elf -O binary kernel8.img

echo ""
echo "✓ Debug version built!"
echo ""
echo "This draws:"
echo "  - Red square (top-left)"
echo "  - Green square (top-right)"
echo "  - Blue square (bottom-left)"
echo "  - Yellow square (bottom-right)"
echo "  - White square (center)"
echo "  THEN tries to run the game"
echo ""
echo "If you see the colored squares, framebuffer works."
echo "If they disappear, game_render() is clearing them."
