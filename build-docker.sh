#!/bin/bash
# Build using Docker (cross-platform solution)

echo "Building kernel using Docker..."

# Build the Docker image
docker build -t rpi-arcade-builder .

# Run and extract the kernel
mkdir -p build
docker run --rm -v "$(pwd)/build:/output" rpi-arcade-builder sh -c "cp kernel8.img /output/"

echo ""
echo "Build complete! kernel8.img is in the build/ directory"
