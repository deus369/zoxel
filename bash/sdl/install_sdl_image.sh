#!/bin/bash

echo " > installing [sdl_image] from source"
# Default output parameter
default_sdl_image_path="build/sdl_image" # linux-sdl_image
# Check if an argument is provided, if not use the default
sdl_image_path="${1:-$default_sdl_image_path}"

sdl_image_url="https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-2.8.2.zip"
sdl_image_zip="build/sdl_image.zip"
sdl_image_source="$sdl_image_path/SDL2_image-2.8.2" # 2.0.5"
sdl_image_include="include/sdl_image"
sdl_image_include_source="$sdl_image_path/include"
lib_file="libSDL2_image.so"
sdl_image_lib_file="lib/$lib_file"
sdl_image_lib_file_source="$sdl_image_path/.libs/$lib_file"
sdl_image_lib_file2="lib/libSDL2_image-2.0.so.0"
sdl_image_lib_file_source2="$sdl_image_path/.libs/libSDL2_image-2.0.so.0"

# download sdl2_image
if [ -d $sdl_image_path ]; then
    echo " > sdl_image source detected [$sdl_image_path]"
else
    echo " + downloading sdl_image source from [$sdl_image_url]"
    wget -O "$sdl_image_zip" "$sdl_image_url"
    unzip -q "$sdl_image_zip" -d "$sdl_image_path"
    rm "$sdl_image_zip"
    # remove folder build/sdl_image/SDL2-2.0.14
    mv "$sdl_image_source"/* "$sdl_image_path"
    rmdir "$sdl_image_source"
fi

if [ -f $sdl_image_lib_file ]; then
    echo " > sdl_image lib detected [$sdl_image_lib_file]"
else
    if [ -f $sdl_image_path/$lib_file ]; then
        echo " > lib file detected [$sdl_image_path/$lib_file]"
    else
        echo " + building [$lib_file]"
        cd $sdl_image_path
        # ./configure
        echo " > cleaning source of sdl_image"
        make clean > /dev/null 2>&1
        echo " > configuring sdl_image"
        ./autogen.sh > /dev/null 2>&1
        ./configure --enable-shared --disable-static > /dev/null 2>&1
        echo " > making sdl_image"
        make > /dev/null 2>&1
        cd ../..
    fi
    if [ ! -f $sdl_image_lib_file_source ]; then
        echo " ! failed to make [$sdl_image_lib_file_source]"
    else
        echo " + copying to [$sdl_image_lib_file]"
        cp $sdl_image_lib_file_source $sdl_image_lib_file
    fi
fi
if [ ! -f $sdl_image_lib_file2 ]; then
    echo " + copying to [$sdl_image_lib_file2]"
    cp $sdl_image_lib_file_source2 $sdl_image_lib_file2
fi

if [ ! -d $sdl_image_include ]; then
    echo " + creating [$sdl_image_include]"
    mkdir $sdl_image_include
    mv $sdl_image_include_source/* $sdl_image_include
else
    echo " > sdl_image include detected [$sdl_image_include]"
fi
