#!/bin/bash

# Define variables
SDL2_URL="https://github.com/libsdl-org/SDL.git"
SDL2_IMAGE_URL="https://github.com/libsdl-org/SDL_image.git"
SDL2_MIXER_URL="https://github.com/libsdl-org/SDL_mixer.git"
sdl_install_directory="build/sdl/sdl"
sdl_image_install_directory="build/sdl/sdl_image"
sdl_mixer_install_directory="build/sdl/sdl_mixer"

if [ -d $sdl_install_directory ]; then
    echo "  > directory exists [$sdl_install_directory]"
else
    echo "  > directory does not exist [$sdl_install_directory]"
    git clone -b release-2.26.x $SDL2_URL $sdl_install_directory
    rm -rf $sdl_install_directory/.git
fi

if [ -d $sdl_image_install_directory ]; then
    echo "  > directory exists [$sdl_image_install_directory]"
else
    echo "  > directory does not exist [$sdl_image_install_directory]"
    git clone -b release-2.6.x $SDL2_IMAGE_URL $sdl_image_install_directory
    rm -rf $sdl_image_install_directory/.git
fi

if [ -d $sdl_mixer_install_directory ]; then
    echo "  > directory exists [$sdl_mixer_install_directory]"
else
    echo "  > directory does not exist [$sdl_mixer_install_directory]"
    git clone -b release-2.6.x $SDL2_MIXER_URL $sdl_mixer_install_directory
    rm -rf $sdl_mixer_install_directory/.git
fi

echo "  > sdl repositories downloaded successfully"
