# Raspberry Pi Bare-Metal Arcade Game

A simple space shooter game written in pure C that boots directly from USB on Raspberry Pi (no operating system required).

## Hardware Requirements

- Raspberry Pi 3B, 3B+, 4, or 5
- USB flash drive (FAT32 formatted, minimum 256MB)
- HDMI monitor
- USB keyboard or GPIO buttons
- Power supply

## GPIO Button Wiring (Optional)

If using physical buttons instead of USB keyboard:

- GPIO 17 → Up
- GPIO 27 → Down
- GPIO 22 → Left
- GPIO 23 → Right
- GPIO 24 → Fire

All buttons should be wired between the GPIO pin and GND (pull-up resistors are configured in software).

## Building

### Install ARM Toolchain

On Ubuntu/Debian:
```bash
sudo apt update
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi gdb-multiarch make
```

On macOS:
```bash
brew install --cask gcc-arm-embedded
```

### Compile

```bash
make
```

This will generate `kernel8.img`.

## Deployment

### 1. Download Raspberry Pi Firmware Files

```bash
wget https://github.com/raspberrypi/firmware/raw/master/boot/bootcode.bin
wget https://github.com/raspberrypi/firmware/raw/master/boot/start4.elf
wget https://github.com/raspberrypi/firmware/raw/master/boot/fixup4.dat
```

### 2. Prepare USB Drive

1. Format USB drive as FAT32
2. Copy these files to the root of the USB drive:
   - `bootcode.bin`
   - `start4.elf`
   - `fixup4.dat`
   - `config.txt` (from this project)
   - `kernel8.img` (compiled from this project)

### 3. Boot

1. Insert USB drive into Raspberry Pi
2. Connect HDMI monitor
3. Power on the Raspberry Pi
4. The game should start automatically!

## Game Controls

### GPIO Buttons
- Up/Down/Left/Right - Move player
- Fire - Shoot bullets

### USB Keyboard (not yet implemented)
USB HID support requires additional driver code.

## Troubleshooting

### Black Screen
- Verify all firmware files are present
- Check HDMI cable and monitor
- Try different USB port
- Ensure config.txt is properly formatted

### No Response
- Check GPIO wiring
- Verify buttons are connected to correct pins
- Test continuity with multimeter

### Won't Boot from USB
- Raspberry Pi 3B may need USB boot enabled in OTP
- Try a different USB drive
- Ensure drive is FAT32 formatted

## Architecture

```
raspberry-pi-arcade/
├── src/
│   ├── boot.S           # Assembly boot code
│   ├── main.c           # Main game loop
│   ├── framebuffer.c/h  # Graphics system
│   ├── mailbox.c/h      # GPU communication
│   ├── gpio.c/h         # Input handling
│   ├── timer.c/h        # Timing functions
│   └── game.c/h         # Game logic
├── Makefile             # Build system
├── linker.ld            # Memory layout
└── config.txt           # Boot configuration
```

## Technical Details

- **Boot Address:** 0x80000
- **Display:** 1280x720, 32-bit RGB
- **Frame Rate:** ~60 FPS
- **Memory:** Direct framebuffer access
- **Hardware:** Direct register manipulation

## Extending the Game

### Add Sprites
Implement bitmap loading and blitting in `framebuffer.c`.

### Add Sound
Use PWM on GPIO pins for audio output.

### Add USB Keyboard Support
Implement USB HID driver (complex, see resources in main documentation).

### Add More Game Objects
Extend the `GameObject` structure in `game.c`.

## Resources

- [BCM2711 ARM Peripherals](https://datasheets.raspberrypi.com/bcm2711/bcm2711-peripherals.pdf)
- [Raspberry Pi Bare Metal Forum](https://www.raspberrypi.org/forums/viewforum.php?f=72)
- [Original Tutorial](raspberry_pi_arcade_game.md)

## License

Public domain. Use freely for educational or commercial purposes.
