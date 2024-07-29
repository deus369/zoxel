#!/bin/bash

# Set the download URL for SDL2
sdl_url="https://github.com/libsdl-org/SDL/releases/download/release-2.30.2/SDL2-devel-2.30.2-VC.zip"
sdl_zip="build/sdl.zip"
sdl_source="build/sdl/SDL2-2.30.2" # SDL2-2.0.14"
sdl_path="build/sdl"
sdl_source="build/sdl/lib/x64/SDL2.dll"
sdl_destination="lib/SDL2.dll"

if [ ! -d $sdl_path ]; then
    mkdir -p "$sdl_path"
    wget -O "$sdl_zip" "$sdl_url"
    unzip -q "$sdl_zip" -d "$sdl_path"
    rm "$sdl_zip"
    # remove folder build/sdl/SDL2-2.0.14
    mv "$sdl_source"/* "$sdl_path"
    rmdir "$sdl_source"
else
    echo " > [$sdl_path] exists"
fi

if [ ! -f $sdl_destination ]; then
    echo " + [$sdl_destination] added"
    cp $sdl_source $sdl_destination
else
    echo " > [$sdl_destination] already exists"
fi

sdl_image_url="https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip"
sdl_image_zip="build/sdl_image.zip"
sdl_image_source="build/sdl_image/SDL2_image-2.8.2" # 2.0.5"
sdl_image_path="build/sdl_image"
sdl_source="build/sdl_image/lib/x64/SDL2_image.dll"
sdl_destination="lib/SDL2_image.dll"

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

sdl_mixer_url="https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-VC.zip"
sdl_mixer_zip="build/sdl_mixer.zip"
sdl_mixer_source="build/sdl_mixer/SDL2_mixer-2.8.0" # 2.0.4"
sdl_mixer_path="build/sdl_mixer"
sdl_source="build/sdl_mixer/lib/x64/SDL2_mixer.dll"
sdl_destination="lib/SDL2_mixer.dll"

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
