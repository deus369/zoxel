#!/bin/bash

sdl2_branch=release-2.26.x # release-2.28.x
sdl2_image_branch=release-2.6.x
sdl2_mixer_branch=release-2.6.x
# Define variables
SDL2_URL="https://github.com/libsdl-org/SDL.git"
SDL2_IMAGE_URL="https://github.com/libsdl-org/SDL_image.git"
SDL2_MIXER_URL="https://github.com/libsdl-org/SDL_mixer.git"
sdl_parent_directory="build/android-sdl"
sdl_install_directory="$sdl_parent_directory/sdl"
sdl_image_install_directory="$sdl_parent_directory/sdl_image"
sdl_mixer_install_directory="$sdl_parent_directory/sdl_mixer"
#sdl2_branch=release-2.28.x # release-2.26.x
#sdl2_extras_branch=release-2.6.x # release-2.26.x
# sdl2_branch=SDL2
# sdl2_image_branch=SDL2
# sdl2_mixer_branch=SDL2
# sdl2_branch=release-2.26.x # fails build

if [ ! -d $sdl_parent_directory ]; then
    echo " + created $sdl_parent_directory"
    mkdir $sdl_parent_directory
fi

if [ -d $sdl_install_directory ]; then
    echo "  > directory exists [$sdl_install_directory]"
else
    echo "  > downloading to [$sdl_install_directory]"
    git clone -b $sdl2_branch $SDL2_URL $sdl_install_directory
    rm -rf $sdl_install_directory/.git
fi

if [ -d $sdl_image_install_directory ]; then
    echo "  > directory exists [$sdl_image_install_directory]"
else
    echo "  > downloading to[$sdl_image_install_directory]"
    git clone -b $sdl2_image_branch $SDL2_IMAGE_URL $sdl_image_install_directory
    rm -rf $sdl_image_install_directory/.git
fi

if [ -d $sdl_mixer_install_directory ]; then
    echo "  > directory exists [$sdl_mixer_install_directory]"
else
    echo "  > downloading to [$sdl_mixer_install_directory]"
    git clone -b $sdl2_mixer_branch $SDL2_MIXER_URL $sdl_mixer_install_directory
    rm -rf $sdl_mixer_install_directory/.git
fi

echo "  > sdl repositories downloaded successfully"

# clear
#if [ -d $sdl_install_directory ]; then
#    echo " > removing sdl [$sdl_install_directory]"
#    rm -R $sdl_install_directory
#fi
#if [ -d $sdl_image_install_directory ]; then
#    echo " > removing sdl_image [$sdl_image_install_directory]"
#    rm -R $sdl_image_install_directory
#fi
#if [ -d $sdl_mixer_install_directory ]; then
#    echo " > removing sdl_mixer [$sdl_mixer_install_directory]"
#    rm -R $sdl_mixer_install_directory
#fi
