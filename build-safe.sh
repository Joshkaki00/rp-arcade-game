#!/bin/bash
# Build safe framebuffer test with timeouts and error handling

export PATH="/Users/joshkaki/.local/aarch64-toolchain/bin:$PATH"

echo "Building safe framebuffer test..."

# Compile
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/boot.S -o boot.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/main_safe.c -o main_safe.o
aarch64-none-elf-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a72 -c src/mailbox_safe.c -o mailbox_safe.o

# Link
aarch64-none-elf-ld -T linker.ld boot.o main_safe.o mailbox_safe.o -o kernel8.elf
aarch64-none-elf-objcopy kernel8.elf -O binary kernel8.img

SIZE=$(ls -lh kernel8.img | awk '{print $5}')

echo ""
echo "✓ Safe framebuffer test built! ($SIZE)"
echo ""
echo "This version:"
echo "  ✓ Has timeout protection for mailbox"
echo "  ✓ Tests if mailbox address is valid before using"
echo "  ✓ Shows 7 colored bands if successful"
echo "  ✓ Won't hang on mailbox failures"
echo ""
echo "Copy to USB and test!"
