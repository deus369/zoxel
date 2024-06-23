#!/bin/bash

debugging=""
disabler="--disable-jpg --disable-tif --disable-webp --disable-avif --disable-bmp --disable-gif --disable-lbm --disable-pcx --disable-pnm --disable-tga --disable-xcf --disable-xpm --disable-svg --disable-qoi --disable-jxl"

echo " > installing [sdl_image] from source"
# Default output parameter
default_sdl_image_path="build/sdl_image" # linux-sdl_image
# Check if an argument is provided, if not use the default
sdl_image_path="${1:-$default_sdl_image_path}"
lib_file_type="${2:-'so'}"
if [ "$lib_file_type" = "dll" ]; then
    lib_file_name="SDL2_image"
else
    lib_file_name="libSDL2_image"
fi
lib_file="$lib_file_name.$lib_file_type"
echo " > sdl path is [$sdl_image_path] lib file [$lib_file]"

version="2.8.2" # 2.0.5"
sdl_image_url="https://github.com/libsdl-org/SDL_image/releases/download/release-$version/SDL2_image-$version.zip"
sdl_image_zip="build/sdl_image.zip"
sdl_image_source="$sdl_image_path/SDL2_image-$version"
sdl_image_include="include/sdl_image"
sdl_image_include_source="$sdl_image_path/include"
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
        if [ -f $sdl_image_lib_file_source ]; then
            echo " > [$sdl_image_lib_file_source] already made"
        else
            cd $sdl_image_path
            # ./configure
            echo " > cleaning source of sdl_image"
            make clean > /dev/null 2>&1
            echo " > configuring sdl_image"
            ./autogen.sh > /dev/null 2>&1
            if [ "$lib_file_type" = "dll" ]; then
                echo "   - configuring for mingw32"
                CPPFLAGS="-I../../include/sdl" ./configure --host=x86_64-w64-mingw32 --enable-shared --disable-static $disabler --with-sdl2-prefix="../sdl" > /dev/null 2>&1
                #  --with-sdl-prefix="../../lib"
            else
                CPPFLAGS="-I../../include/sdl" ./configure --enable-shared --disable-static $disabler --with-sdl-prefix="../../lib" > /dev/null 2>&1
            fi
            if [ $? -ne 0 ]; then
                echo " ! sdl_image configure failed"
                exit
            else
                echo " + configure successful"
            fi
            echo " > making sdl_image"
            make > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                echo " ! sdl_image make failed"
                exit
            else
                echo " + make successful"
            fi
            cd ../..
        fi
    fi
    if [ ! -f $sdl_image_lib_file_source ]; then
        echo " ! failed to make [$sdl_image_lib_file_source]"
    else
        echo " + copying to [$sdl_image_lib_file]"
        cp $sdl_image_lib_file_source $sdl_image_lib_file
    fi
fi

if [ ! "$lib_file_type" == "dll" ]; then
    if [ ! -f $sdl_image_lib_file2 ]; then
        echo " + copying to [$sdl_image_lib_file2]"
        cp $sdl_image_lib_file_source2 $sdl_image_lib_file2
    fi
fi

if [ ! -d $sdl_image_include ]; then
    echo " + creating [$sdl_image_include]"
    mkdir $sdl_image_include
    mv $sdl_image_include_source/* $sdl_image_include
else
    echo " > sdl_image include detected [$sdl_image_include]"
fi
