# Use Docker to build the kernel
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc-aarch64-linux-gnu \
    binutils-aarch64-linux-gnu \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build
COPY . .

# Override toolchain in Makefile
RUN make ARMGNU=aarch64-linux-gnu

# Output will be in /build/kernel8.img
CMD ["cp", "kernel8.img", "/output/"]
