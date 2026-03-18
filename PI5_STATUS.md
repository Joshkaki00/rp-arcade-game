# Raspberry Pi 5 Status & Workaround

## Current Status

✅ **Working:**
- Framebuffer graphics via GPU mailbox
- Kernel boots and runs
- Display output (1280x720)

⚠️ **Not Working:**
- GPIO button input (requires PCIe/RP1 initialization)

## The Problem

Raspberry Pi 5 introduced a major architectural change: GPIO pins are now controlled by an **RP1 chip** accessed via PCIe at address `0x1F000D0000` instead of direct memory-mapped I/O like Pi 4 (`0xFE200000`).

To access RP1 peripherals in bare-metal code, you must:
1. Initialize the PCIe controller
2. Set up address translation for 40-bit RP1 address space
3. Access GPIO through the RP1 peripheral interface

This is complex and beyond the scope of this simple demo project.

## Workaround: Test Display Without Input

You can still test the display and rendering system on Pi 5, even without GPIO input.

### Option 1: Auto-Demo Mode

Modify `src/game.c` to run in automatic demo mode:

```c
void game_update(void) {
    // Auto-play mode for Pi 5 testing
    static int auto_move_counter = 0;
    
    // Move player automatically
    if (auto_move_counter < 60) {
        player.x += 5;  // Move right
    } else if (auto_move_counter < 120) {
        player.x -= 5;  // Move left
    } else {
        auto_move_counter = 0;
    }
    auto_move_counter++;
    
    // Auto-fire
    if (auto_move_counter % 20 == 0) {
        fire_bullet();
    }
    
    // Rest of game logic stays the same...
```

### Option 2: USB Keyboard Support

Implementing a USB HID driver would provide input on Pi 5, but this requires:
- USB controller initialization
- USB protocol handling
- HID keyboard parsing

This is a significant undertaking for a bare-metal project.

## Future Work

To fully support Pi 5, the project would need:

1. **PCIe Initialization Code**
   - Configure BCM2712 PCIe controller
   - Enable 40-bit address translation
   - Map RP1 peripheral space

2. **RP1 GPIO Driver**
   - Use RP1 GPIO register layout (different from BCM)
   - Implement RP1-specific pull-up/down control
   - Handle RP1 peripheral clocking

3. **Or: USB HID Driver**
   - Initialize xHCI USB controller
   - Implement USB enumeration
   - Parse HID keyboard reports
   - Map keyboard to game controls

## References

- [RP1 Peripherals Datasheet](https://datasheets.raspberrypi.com/rp1/rp1-peripherals.pdf)
- [BCM2712 Datasheet](https://datasheets.raspberrypi.com/bcm2712/bcm2712-peripherals.pdf)
- [Bare Metal Pi 5 Discussion](https://raspberrypi.stackexchange.com/questions/153971)

## Recommendation

**For learning bare-metal programming, use Raspberry Pi 4 or earlier.** Pi 5's added complexity (PCIe, RP1 chip) makes it less suitable for introductory bare-metal projects.

If you only have Pi 5, you can still:
- Learn framebuffer graphics
- Understand mailbox communication
- Practice ARM64 assembly
- Implement the auto-demo workaround above
