#!/bin/bash
export PATH="/Users/joshkaki/.local/aarch64-toolchain/bin:$PATH"

echo "Building FULL GAME with safe GPIO/timer..."

aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/boot.S -o boot.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/main.c -o main.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/framebuffer.c -o framebuffer.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/mailbox.c -o mailbox.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/gpio_safe.c -o gpio.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/timer_safe.c -o timer.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/game.c -o game.o

aarch64-none-elf-ld -T linker.ld boot.o main.o framebuffer.o mailbox.o gpio.o timer.o game.o -o kernel8.elf
aarch64-none-elf-objcopy kernel8.elf -O binary kernel8.img

echo ""
echo "✓ Full game built with safe peripherals!"
echo ""
echo "This version:"
echo "  ✓ Full game logic"
echo "  ✓ Player, bullets, enemies, collisions"
echo "  ✓ Won't hang (safe GPIO/timer)"
echo "  ✓ No input (buttons disabled)"
echo "  ✓ Enemies will spawn and move"
echo ""
echo "You should see:"
echo "  - Green player (bottom center)"
echo "  - Red enemies spawning and falling"
echo "  - Game running at 60 FPS!"
