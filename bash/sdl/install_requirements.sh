#!/bin/bash

source bash/util/package_util.sh

echo "installing sdl build requirements"
install_first_library "gcc"
install_first_library "make"

#sdl requirements
install_first_library "libx11"
install_first_library "libxext" # libxext-dev ?
install_first_library "xorg-server-devel"
install_first_library "libxcb"

# sdl requirements
install_first_library "wayland-devel" "libwayland-dev" "wayland" "wayland-dev"
install_first_library "libdecor-0-dev" "libdecor"
install_first_library "libxkbcommon" "libxkbcommon-dev" "libxkbcommon-devel"
install_first_library "pipewire"
install_first_library "libpulse" "libpulse-dev" "libpulse-libs-devel"
install_first_library "jack2" "libjack-dev"
install_first_library "libdrm" "libdrm-dev"
install_first_library "mesa-libgl" "libgbm-dev" "mesa-libgbm-devel"

# requirements for SDL2_image
install_first_library "libjxl-dev" "libjxl"
install_first_library "libtiff"
install_first_library "libwebp"

# requirements for sdl2_mixer
install_first_library "libogg-dev" "libogg"
install_first_library "libopus-dev" "opus" "opus-devel"
