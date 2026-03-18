# Raspberry Pi 5 Quick Start Guide

## Problem

You're seeing this error:
```
Device-tree file "bcm2717-rpi-5-dbt" not found
The installed operating system does not indicate support for rp5
Update the OS or set os_check=0 in config.txt to skip this check.
```

## Solution

I've updated the `config.txt` file to include `os_check=0` which tells the Pi 5 firmware to skip the OS check for bare-metal kernels.

## Current Status

✅ **Fixed**: Kernel now boots on Pi 5  
⚠️ **Limited**: GPIO buttons don't work (Pi 5 architectural limitation)  
✅ **Workaround**: Auto-demo mode available

## Quick Setup for Pi 5

### Step 1: Build the auto-demo version

```bash
# Enable auto-demo mode (no GPIO input needed)
./enable-pi5-demo.sh

# Build the kernel
./build.sh
```

### Step 2: Copy updated config.txt to USB

Make sure you copy the **updated** `config.txt` to your USB drive (it now includes `os_check=0`).

Required files on USB:
- `bootcode.bin`
- `start4.elf`
- `fixup4.dat`
- `config.txt` ← **Must be the updated version!**
- `kernel8.img`

### Step 3: Boot and watch

Your Pi 5 will now:
- Boot successfully ✓
- Display the game at 1280x720 ✓
- Player ship moves automatically left/right
- Auto-fires bullets
- Enemies spawn and move down
- Collisions are detected and scored
- Cyan border indicates demo mode is active

## Why GPIO Doesn't Work on Pi 5

Raspberry Pi 5 introduced a major change:
- **Pi 4 and earlier**: GPIO at `0xFE200000` (direct memory access)
- **Pi 5**: GPIO on RP1 chip at `0x1F000D0000` (requires PCIe initialization)

Accessing RP1 requires:
1. PCIe controller initialization
2. 40-bit address translation setup
3. RP1 peripheral driver

This is beyond the scope of a simple bare-metal demo project.

## What Works

| Feature | Pi 4 | Pi 5 |
|---------|------|------|
| Framebuffer graphics | ✅ | ✅ |
| 60 FPS game loop | ✅ | ✅ |
| GPIO input | ✅ | ❌ |
| Auto-demo mode | ✅ | ✅ |

## Alternative: Use Raspberry Pi 4

For full GPIO control in bare-metal projects, **Raspberry Pi 4 or earlier is recommended**. Pi 5's additional complexity makes it less ideal for learning bare-metal programming.

## Troubleshooting

### Still getting "Device-tree file" error?
- Make sure you copied the **updated** `config.txt` that includes `os_check=0`
- The config.txt must be in the root of your USB drive

### Black screen?
- Verify all 5 files are on USB
- Try a different HDMI port
- Check that USB drive is FAT32 formatted

### Want to restore GPIO mode for Pi 4?
```bash
cp src/game.c.original src/game.c
./build.sh
```

## More Information

See `PI5_STATUS.md` for technical details about Pi 5 limitations and potential solutions.
