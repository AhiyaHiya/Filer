FROM ubuntu:22.04

# Set non-interactive frontend to avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies for building gtk and gtkmm
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    python3 \
    python3-pip \
    pkg-config \
    libx11-dev \
    libxrandr-dev \
    libxrender-dev \
    libxext-dev \
    libxi-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxdamage-dev \
    libxfixes-dev \
    libgtk-4-dev \
    autoconf \
    automake \
    libtool \
    && rm -rf /var/lib/apt/lists/*

# Install Meson via pip (vcpkg uses its own Meson, but this ensures compatibility)
RUN pip3 install meson

# Set up vcpkg
WORKDIR /app
RUN git clone https://github.com/microsoft/vcpkg.git /app/vcpkg && \
    /app/vcpkg/bootstrap-vcpkg.sh

# Copy the project source from the root of the build context
COPY . /app/Filer
WORKDIR /app/Filer

# Configure vcpkg and build the project
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/app/vcpkg/scripts/buildsystems/vcpkg.cmake
RUN cmake --build build

CMD ["/bin/bash"]