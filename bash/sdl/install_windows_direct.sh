#!/bin/bash

# when on windows we need to download builds directly, since i couldn't get compiling here to work
sdl_path="build/windows-sdl"
sdl_image_path="build/windows-sdl_image"
sdl_mixer_path="build/windows-sdl_mixer"

# Set the download URL for SDL2
sdl_url="https://github.com/libsdl-org/SDL/releases/download/release-2.30.2/SDL2-devel-2.30.2-VC.zip"
sdl_zip="build/sdl.zip"
sdl_zip_directory="$sdl_path/SDL2-2.30.2" # SDL2-2.0.14"
sdl_source="$sdl_path/lib/x64/SDL2.dll"
sdl_destination="lib/SDL2.dll"

sdl_image_url="https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip"
sdl_image_zip="build/sdl_image.zip"
sdl_image_source="$sdl_image_path/SDL2_image-2.8.2" # 2.0.5"
sdl_source="$sdl_image_path/lib/x64/SDL2_image.dll"
sdl_destination="lib/SDL2_image.dll"

sdl_mixer_url="https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-VC.zip"
sdl_mixer_zip="build/sdl_mixer.zip"
sdl_mixer_source="$sdl_mixer_path/SDL2_mixer-2.8.0" # 2.0.4"
sdl_source="$sdl_mixer_path/lib/x64/SDL2_mixer.dll"
sdl_destination="lib/SDL2_mixer.dll"

# SDL
if [ ! -d $sdl_path ]; then
    echo " > making sdl path [$sdl_path]"
    mkdir -p "$sdl_path"
    wget -O "$sdl_zip" "$sdl_url"
    unzip -q "$sdl_zip" -d "$sdl_path"
    rm "$sdl_zip"
    # remove folder build/sdl/SDL2-2.0.14
    mv "$sdl_zip_directory"/* "$sdl_path"
    rmdir "$sdl_zip_directory"
else
    echo " > [$sdl_path] exists"
fi

if [ ! -f $sdl_destination ]; then
    echo " + [$sdl_destination] added"
    cp $sdl_source $sdl_destination
else
    echo " > [$sdl_destination] already exists"
fi

# SDL_IMAGE
if [ ! -d $sdl_image_path ]; then
    mkdir -p "$sdl_image_path"
    wget -O "$sdl_image_zip" "$sdl_image_url"
    unzip -q "$sdl_image_zip" -d "$sdl_image_path"
    rm "$sdl_image_zip"
    # remove folder build/sdl/SDL2-2.0.14
    mv "$sdl_image_source"/* "$sdl_image_path"
    rmdir "$sdl_image_source"
else
    echo " > [$sdl_image_path] exists"
fi

if [ ! -f $sdl_destination ]; then
    echo " + [$sdl_destination] added"
    cp $sdl_source $sdl_destination
else
    echo " > [$sdl_destination] already exists"
fi

# SDL_MIXER
if [ ! -d $sdl_mixer_path ]; then
    mkdir -p "$sdl_mixer_path"
    wget -O "$sdl_mixer_zip" "$sdl_mixer_url"
    unzip -q "$sdl_mixer_zip" -d "$sdl_mixer_path"
    rm "$sdl_mixer_zip"
    # remove folder build/sdl/SDL2-2.0.14
    mv "$sdl_mixer_source"/* "$sdl_mixer_path"
    rmdir "$sdl_mixer_source"
else
    echo " > [$sdl_mixer_path] exists"
fi

if [ ! -f $sdl_destination ]; then
    echo " + [$sdl_destination] added"
    cp $sdl_source $sdl_destination
else
    echo " > [$sdl_destination] already exists"
fi
