#!/bin/bash
# Install dependencies for GLFW-Snake project

sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    clang \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libwayland-dev \
    wayland-protocols \
    libxkbcommon-dev \
    pkg-config
