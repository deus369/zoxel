#!/bin/bash

echo "> checking linux packages"

source bash/util/package_util.sh

install_first_library "gcc"
install_first_library "wget"

# bash bash/freetype/install_requirements.sh
bash bash/sdl/install_requirements.sh

# installs sdl for system
# bash bash/sdl/install_sdl_on_system.sh
#  [sdl2] is installed with pacman
# [sdl2_image] is installed with pacman
# [sdl2_mixer] is installed with pacman


# install_first_library "libgl"

# install_first_library "libvulkan-dev" "vulkan-devel" "vulkan-headers"

# wget requirements
# install_first_library "libglew-dev" "glew" "libglew"

# install_first_library "libfreetype6-dev" "freetype2"

# debug requuired tools
# install_first_library "valgrind"
# install_first_library "gdb"

#if is_steam_deck; then
    # for some reason had to manually install gcc
    # for linux/assert.h
    #if ! has_library "glibc"; then
    #    install_library "glibc"
    #fi
    # for linux/errno.h
    #if ! has_library "linux-api-headers"; then
    #    install_library "linux-api-headers"
    #fi
    # this kinda needs updating? reinstalling?
    #if ! has_library "sdl2"; then
    #    install_library "sdl2"
    #fi
    
    # if ! has_library "lib32-glibc"; then
    #     install_library "lib32-glibc"
    # fi
    # if ! has_library "linux-headers"; then
    #     install_library "linux-headers"
    # fi
    # if ! has_library "base-devel"; then
    #     install_library "base-devel"
    # fi
#fi
