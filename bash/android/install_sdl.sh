#!/bin/bash

# Define variables
SDL2_URL="https://github.com/libsdl-org/SDL.git"
SDL2_IMAGE_URL="https://github.com/libsdl-org/SDL_image.git"
SDL2_MIXER_URL="https://github.com/libsdl-org/SDL_mixer.git"
sdl_install_directory="build/sdl/sdl"
sdl_image_install_directory="build/sdl/sdl_image"
sdl_mixer_install_directory="build/sdl/sdl_mixer"

# Clone repositories
git clone $SDL2_URL $sdl_install_directory
git clone $SDL2_IMAGE_URL $sdl_image_install_directory
git clone $SDL2_MIXER_URL $sdl_mixer_install_directory

# Clean up
rm -rf $sdl_install_directory/.git
rm -rf $sdl_image_install_directory/.git
rm -rf $sdl_mixer_install_directory/.git

echo "SDL2, SDL2_image, and SDL2_mixer repositories downloaded successfully!"
