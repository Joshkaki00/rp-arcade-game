#!/bin/bash
# Add AArch64 toolchain to shell PATH permanently

TOOLCHAIN_PATH='export PATH="$HOME/.local/aarch64-toolchain/bin:$PATH"'

if [ -f ~/.zshrc ]; then
    if grep -q "aarch64-toolchain" ~/.zshrc; then
        echo "✓ Toolchain already in ~/.zshrc"
    else
        echo "" >> ~/.zshrc
        echo "# AArch64 bare-metal toolchain" >> ~/.zshrc
        echo "$TOOLCHAIN_PATH" >> ~/.zshrc
        echo "✓ Added toolchain to ~/.zshrc"
        echo ""
        echo "Run this to activate in current shell:"
        echo "  source ~/.zshrc"
    fi
else
    echo "~/.zshrc not found. Add this line manually to your shell config:"
    echo "  $TOOLCHAIN_PATH"
fi
