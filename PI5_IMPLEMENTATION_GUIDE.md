# Raspberry Pi 5 Bare-Metal Implementation Guide

**Status:** Not yet implemented  
**Difficulty:** Significant but absolutely doable  
**Resources Available:** FREE datasheets, Linux source code, community forums  

---

## This IS Possible

Evans & Sutherland built real-time 3D graphics from scratch in the 1960s. IBM built PC architecture. You can figure out Pi 5 peripheral access in 2026 with:
- Free documentation
- Open source reference implementations (Linux)
- A community doing the same thing

**This document is for when you're ready.**

---

## Required Knowledge (You'll Learn This)

### 1. PCIe Basics
- Memory-mapped configuration space
- Base Address Registers (BARs)
- Device enumeration

**Learn from:**
- PCIe Base Specification (free from PCI-SIG)
- Linux `drivers/pci/` source code
- "PCI Express System Architecture" book (or find free resources online)

### 2. ARM64 Memory Management
- MMU configuration
- Page tables
- Address translation

**Learn from:**
- ARM Architecture Reference Manual (free download)
- Linux `arch/arm64/mm/` source code
- Bare-metal tutorials online

### 3. Device Tree (Optional but Helpful)
- Understanding hardware descriptions
- Finding peripheral addresses

**Learn from:**
- devicetree.org specification
- `/boot/firmware/bcm2712-rpi-5-b.dtb` on Pi OS
- `dtc` command to decompile device trees

---

## Step-by-Step Implementation Path

### Phase 1: Find the Addresses (1-2 days)

**Goal:** Figure out where RP1 is mapped

**Tasks:**
1. Boot Raspberry Pi OS on your Pi 5
2. Check `/proc/iomem` to see RP1 mapping
3. Examine device tree: `dtc -I dtb -O dts /boot/firmware/bcm2712-rpi-5-b.dtb`
4. Read BCM2712 datasheet for PCIe controller addresses
5. Document the addresses you find

**Expected addresses (to verify):**
- RP1 Base: `0x1F00000000` (from community reports)
- RP1 GPIO: `0x1F000D0000` (from community reports)
- BCM2712 PCIe: Check datasheet
- Mailbox: Different from Pi 4's `0xFE00B880`

### Phase 2: Get Framebuffer Working (2-3 days)

**Goal:** White screen on Pi 5 (what we achieved on Pi 4)

**Tasks:**
1. Find correct mailbox address for Pi 5
2. Test mailbox communication
3. Request framebuffer same as Pi 4 code
4. Verify you can draw pixels

**Reference code:**
- Our `src/main_white.c` (working Pi 4 version)
- Modify only the mailbox address
- Everything else should be similar

**Likely issues:**
- Different mailbox base address
- Possibly different property tags supported
- May need `os_check=0` in config.txt (we already added this)

### Phase 3: Initialize PCIe (3-5 days)

**Goal:** Access RP1 chip from bare-metal code

**Study these:**
```bash
# On Pi OS:
sudo cat /proc/iomem | grep -i rp1
lspci -vv  # See PCIe devices
```

**Implementation:**
```c
// 1. Configure BCM2712 PCIe controller
// Find controller base from BCM2712 datasheet
#define PCIE_BASE 0x????????  // TODO: Find in datasheet

// 2. Set up PCIe memory window
// Map RP1's physical address space
// This is where Linux does it: drivers/pci/controller/pcie-brcmstb.c

// 3. Access RP1 via mapped memory
volatile uint32_t *rp1_base = (volatile uint32_t*)0x1F00000000;
// Now you can access RP1 peripherals
```

**Linux reference:**
- `drivers/pci/controller/pcie-brcmstb.c`
- `arch/arm64/boot/dts/broadcom/bcm2712-rpi-5-b.dts`

### Phase 4: RP1 GPIO (1-2 days)

**Goal:** Read GPIO pins, control LEDs

**RP1 GPIO addresses (from datasheet):**
```c
#define RP1_GPIO_BASE    0x1F000D0000

// Similar registers to BCM GPIO:
#define RP1_GPIO_CTRL    (RP1_GPIO_BASE + offset)
#define RP1_GPIO_STATUS  (RP1_GPIO_BASE + offset)
// Check RP1 datasheet for exact offsets
```

**Tasks:**
1. Read RP1 Peripherals PDF (free download)
2. Find GPIO register offsets
3. Implement gpio_set_input, gpio_read functions
4. Test by reading a button or blinking LED

**The registers are similar to Pi 4, just different offsets.**

### Phase 5: Timer (1 day)

**Goal:** Accurate timing for game loop

**Options:**
1. Use ARM generic timer (built into CPU, easy)
2. Use RP1 timer (requires RP1 access)
3. Keep using software timing if it works

**ARM Generic Timer (recommended):**
```c
// This timer is in the CPU, should work on Pi 5
static inline uint64_t read_cntpct(void) {
    uint64_t val;
    asm volatile("mrs %0, cntpct_el0" : "=r" (val));
    return val;
}
```

This is actually **easier** than Pi 4's peripheral timer.

---

## Resources You Need

### Free Datasheets
1. **BCM2712 ARM Peripherals**
   - https://datasheets.raspberrypi.com/bcm2712/bcm2712-peripherals.pdf
   - Main CPU documentation

2. **RP1 Peripherals**
   - https://datasheets.raspberrypi.com/rp1/rp1-peripherals.pdf
   - GPIO, SPI, I2C, PWM, etc.

3. **ARM Cortex-A76 Core**
   - developer.arm.com/documentation
   - CPU features and registers

### Linux Source Code (Free Reference Implementation)
```bash
# Clone Raspberry Pi kernel
git clone --depth=1 https://github.com/raspberrypi/linux.git

# Key files to study:
# drivers/pci/controller/pcie-brcmstb.c  - PCIe init
# drivers/gpio/gpio-rp1.c                - GPIO driver
# arch/arm64/boot/dts/broadcom/bcm2712*  - Device tree
```

### Community Resources
- Raspberry Pi Forums: Bare Metal section
- raspberrypi.stackexchange.com
- GitHub bare-metal Pi 5 projects (search for them)

### Tools
```bash
# On Raspberry Pi OS:
dtc         # Device tree compiler
lspci       # See PCIe devices
/proc/iomem # See memory mappings
dmesg       # Kernel messages about hardware init
```

---

## Debug Strategy

### Start Small
1. ✅ Boot minimal kernel (we did this - it works on Pi 5!)
2. ⬜ Get framebuffer working (find mailbox address)
3. ⬜ Blink the power LED (RP1 GPIO)
4. ⬜ Read a button (RP1 GPIO input)
5. ⬜ Full game with input

### Each Step Proves Something
- Minimal kernel → CPU boots, firmware works
- Framebuffer → Mailbox communication works
- LED blink → RP1 access works, GPIO output works
- Button read → GPIO input works
- Full game → Everything integrated

### When You're Stuck
1. Check what Linux does
2. Read the datasheet section carefully
3. Ask on forums with specific questions
4. Test with smallest possible code

---

## Timeline Estimate

**If you dedicate focused time:**
- Weekend project (16 hours): Probably not enough
- Week (40 hours): Possible to get working
- Two weeks (80 hours): Comfortable timeline
- Month (spare time): Realistic for learning + implementing

**This assumes learning as you go.**

---

## You WILL Figure This Out

Evans & Sutherland pioneered computer graphics.  
IBM created the PC.  
Linus Torvalds wrote Linux.  
You can access RP1 GPIO registers.

**The information exists. The hardware is documented. You have the tools.**

When you get it working, document it and share it. Future you will thank yourself, and so will everyone else with a Pi 5.

---

## Mark This

**"I'm just not qualified, but I will be."**

Come back to this document when you're ready. Everything you need to know is learnable. The documentation is free. The examples exist in Linux.

Pi 5 bare-metal is waiting for you.

---

**Next Steps When Ready:**
1. Download the datasheets
2. Clone the Linux kernel source
3. Boot Pi OS and run `cat /proc/iomem`
4. Start with Phase 1: Find the addresses

**You've got this.** 🚀
