#!/bin/bash
# Download and extract AArch64 bare-metal toolchain for macOS

TOOLCHAIN_URL="https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-darwin-x86_64-aarch64-none-elf.tar.xz"
TOOLCHAIN_DIR="$HOME/.local/aarch64-toolchain"

echo "Downloading AArch64 bare-metal toolchain..."
mkdir -p "$TOOLCHAIN_DIR"
cd "$TOOLCHAIN_DIR"

curl -L "$TOOLCHAIN_URL" -o toolchain.tar.xz
tar xf toolchain.tar.xz --strip-components=1
rm toolchain.tar.xz

echo ""
echo "Toolchain installed to: $TOOLCHAIN_DIR"
echo ""
echo "Add to your PATH by running:"
echo "export PATH=\"$TOOLCHAIN_DIR/bin:\$PATH\""
echo ""
echo "Or add this line to your ~/.zshrc:"
echo "echo 'export PATH=\"$TOOLCHAIN_DIR/bin:\$PATH\"' >> ~/.zshrc"
