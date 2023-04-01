#!/bin/bash
# the script will use a series of sdl library names and apt-get or pacman to install sdl libraries

source bash/util/package_util.sh

install_first_library "libsdl2-dev" "SDL2-devel" "libsdl2" "libsdl2-2.0" "sdl2"
install_first_library "libsdl2-image-dev" "SDL2_image-devel" "libsdl2_image" "libsdl2-image-2.0" "sdl2_image"
install_first_library "libsdl2-mixer-dev" "SDL2_mixer-devel" "libsdl2_mixer" "libsdl2-mixer-2.0" "sdl2_mixer"