#!/bin/bash

echo "> checking linux packages"

source bash/util/package_util.sh

if ! has_library "gcc"; then
    install_library "gcc"
fi

echo "> installing opengl"
install_first_library "libgl"

echo "> installing glew"
install_first_library "libglew-dev" "glew" "libglew"

echo "> installing vulkan"
install_first_library "libvulkan-dev" "vulkan-devel" "vulkan-headers"

echo "> installing wget"
install_first_library "wget"

# debug requuired tools
echo "> installing valgrind"
install_first_library "valgrind"
echo "> installing gdb"
install_first_library "gdb"

bash bash/sdl/install_sdl.sh

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
