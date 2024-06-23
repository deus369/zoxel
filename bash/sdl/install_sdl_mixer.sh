#!/bin/bash

disabler="--disable-music-mod --disable-music-midi --disable-music-ogg --disable-music-flac --disable-music-mp3 --disable-music-opus --disable-music-mod-modplug"

echo " > installing [sdl_mixer] from source"
# Default output parameter
default_sdl_mixer_path="build/sdl_mixer" # linux-sdl_image
# Check if an argument is provided, if not use the default
sdl_mixer_path="${1:-$default_sdl_mixer_path}"
lib_file_type="${2:-'so'}"
if [ "$lib_file_type" = "dll" ]; then
    lib_file_name="SDL2_mixer"
else
    lib_file_name="libSDL2_mixer"
fi
lib_file="$lib_file_name.$lib_file_type"
echo " > sdl path is [$sdl_mixer_path] lib file [$lib_file]"

sdl_mixer_url="https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-2.8.0.zip"
sdl_mixer_zip="build/sdl_mixer.zip"
sdl_mixer_source="$sdl_mixer_path/SDL2_mixer-2.8.0" # 2.0.4"
sdl_mixer_include="include/sdl_mixer"
sdl_mixer_include_source="$sdl_mixer_path/include"
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
        if [ -f $sdl_mixer_lib_file_source ]; then
            echo " > [$sdl_mixer_lib_file_source] already made"
        else
            cd $sdl_mixer_path
            echo " > cleaning source of sdl_mixer"
            make clean > /dev/null 2>&1
            echo " > configuring sdl_mixer"
            ./autogen.sh > /dev/null 2>&1
            if [ "$lib_file_type" = "dll" ]; then
                echo "   - configuring for mingw32"
                CPPFLAGS="-I../../include/sdl" ./configure --host=x86_64-w64-mingw32 --enable-shared --disable-static $disabler --with-sdl2-prefix="../sdl" > /dev/null 2>&1
                #  "../../lib/sdl-dll"
            else
                ./configure --enable-shared --disable-static $disabler --with-sdl-prefix="../../lib" > /dev/null 2>&1
            fi
            if [ $? -ne 0 ]; then
                echo " ! sdl_mixer configure failed"
                exit
            else
                echo " + configure successful"
            fi
            echo " > making sdl_mixer"
            make # > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                echo " ! sdl_mixer make failed"
                exit
            else
                echo " + make successful"
            fi
            cd ../..
        fi
    fi
    if [ ! -f $sdl_mixer_lib_file_source ]; then
        echo " ! failed to make [$sdl_mixer_lib_file_source]"
    else
        echo " + copying to [$sdl_mixer_lib_file]"
        cp $sdl_mixer_lib_file_source $sdl_mixer_lib_file
    fi
fi

if [ ! "$lib_file_type" == "dll" ]; then
    if [ ! -f $sdl_mixer_lib_file2 ]; then
        echo " + copying to [$sdl_mixer_lib_file2]"
        cp $sdl_mixer_lib_file_source2 $sdl_mixer_lib_file2
    fi
fi


if [ ! -d $sdl_mixer_include ]; then
    echo " + creating [$sdl_mixer_include]"
    mkdir $sdl_mixer_include
    mv $sdl_mixer_include_source/* $sdl_mixer_include
else
    echo " > sdl_mixer include detected [$sdl_mixer_include]"
fi
