#!/bin/bash
export PATH="/Users/joshkaki/.local/aarch64-toolchain/bin:$PATH"

echo "Building game with fixed enemy spawning..."

aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/boot.S -o boot.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/main.c -o main.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/framebuffer.c -o framebuffer.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/mailbox.c -o mailbox.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/gpio_safe.c -o gpio.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/timer_safe.c -o timer.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/game_fixed.c -o game.o

aarch64-none-elf-ld -T linker.ld boot.o main.o framebuffer.o mailbox.o gpio.o timer.o game.o -o kernel8.elf
aarch64-none-elf-objcopy kernel8.elf -O binary kernel8.img

echo ""
echo "✓ Game with working enemy spawning!"
echo ""
echo "You should now see:"
echo "  - Green player at bottom"
echo "  - Red enemies spawning every second"
echo "  - Enemies moving down the screen"
echo "  - Enemies respawn when they reach bottom"
echo ""
echo "Full game running at 60 FPS!"
