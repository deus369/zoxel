#!/bin/bash

echo " > installing [sdl_mixer] from source"
# Default output parameter
default_sdl_mixer_path="build/sdl_mixer" # linux-sdl_image
# Check if an argument is provided, if not use the default
sdl_mixer_path="${1:-$default_sdl_mixer_path}"

sdl_mixer_url="https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-2.8.0.zip"
sdl_mixer_zip="build/sdl_mixer.zip"
sdl_mixer_source="$sdl_mixer_path/SDL2_mixer-2.8.0" # 2.0.4"
sdl_mixer_include="include/sdl_mixer"
sdl_mixer_include_source="$sdl_mixer_path/include"
lib_file="libSDL2_mixer.so"
sdl_mixer_lib_file="lib/$lib_file"
sdl_mixer_lib_file_source="$sdl_mixer_path/build/.libs/$lib_file"
sdl_mixer_lib_file2="lib/libSDL2_mixer-2.0.so.0"
sdl_mixer_lib_file_source2="$sdl_mixer_path/build/.libs/libSDL2_mixer-2.0.so.0"

# download sdl2_mixer
if [ -d $sdl_mixer_path ]; then
    echo " > sdl_mixer source detected [$sdl_mixer_path]"
else
    echo " + downloading sdl_mixer source from [$sdl_mixer_url]"
    wget -O "$sdl_mixer_zip" "$sdl_mixer_url" > /dev/null 2>&1
    echo " + unzipping [$sdl_mixer_path]"
    unzip -q "$sdl_mixer_zip" -d "$sdl_mixer_path" > /dev/null 2>&1
    echo " + deleting zip [$sdl_mixer_zip]"
    rm "$sdl_mixer_zip"
    # remove folder build/sdl_mixer/SDL2-2.0.14
    mv "$sdl_mixer_source"/* "$sdl_mixer_path"
    rmdir "$sdl_mixer_source"
fi

if [ ! -f $sdl_mixer_lib_file ]; then
    # remove folder build/sdl/SDL2-2.0.14
    if [ -f $sdl_mixer_path/$lib_file ]; then
        echo " > lib file detected [$sdl_mixer_path/$lib_file]"
    else
        echo " + building [$lib_file]"
        cd $sdl_mixer_path
        echo " > cleaning source of sdl_mixer"
        make clean > /dev/null 2>&1
        echo " > configuring sdl_mixer"
        ./autogen.sh > /dev/null 2>&1
        ./configure --enable-shared --disable-static > /dev/null 2>&1
        echo " > making sdl_mixer"
        make > /dev/null 2>&1
        cd ../..
    fi
    if [ ! -f $sdl_mixer_lib_file_source ]; then
        echo " ! failed to make [$sdl_mixer_lib_file_source]"
    else
        echo " + copying to [$sdl_image_lib_file]"
        cp $sdl_mixer_lib_file_source $sdl_mixer_lib_file
    fi
fi
if [ ! -f $sdl_mixer_lib_file2 ]; then
    echo " + copying to [$sdl_mixer_lib_file2]"
    cp $sdl_mixer_lib_file_source2 $sdl_mixer_lib_file2
fi


if [ ! -d $sdl_mixer_include ]; then
    echo " + creating [$sdl_mixer_include]"
    mkdir $sdl_mixer_include
    mv $sdl_mixer_include_source/* $sdl_mixer_include
else
    echo " > sdl_mixer include detected [$sdl_mixer_include]"
fi
