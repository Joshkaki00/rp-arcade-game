#!/bin/bash
# Enable auto-demo mode for Raspberry Pi 5 testing
# This allows you to see the game running without GPIO input

echo "Setting up for Raspberry Pi 5 auto-demo mode..."

# Backup original game.c
if [ ! -f src/game.c.original ]; then
    cp src/game.c src/game.c.original
    echo "✓ Backed up original game.c"
fi

# Replace game.c with demo version
cp src/game_demo.c src/game_working.c

# Modify the demo flag to enable auto-demo
sed 's/#define AUTO_DEMO_MODE 0/#define AUTO_DEMO_MODE 1/' src/game_demo.c > src/game.c

echo "✓ Enabled AUTO_DEMO_MODE in game.c"
echo ""
echo "Now rebuild:"
echo "  ./build.sh"
echo ""
echo "The game will run automatically with:"
echo "  - Player moving left/right"
echo "  - Auto-firing bullets"
echo "  - Enemies spawning and moving"
echo "  - Cyan border indicating demo mode"
echo ""
echo "To restore GPIO input mode:"
echo "  cp src/game.c.original src/game.c"
echo "  ./build.sh"
