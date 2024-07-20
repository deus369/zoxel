#!/bin/bash

echo " ====== ====== ====== ====== ====== ======"
echo " > installing [sdl] from source"
# Default output parameter
default_sdl_path="build/sdl" # linux-sdl_image
# Check if an argument is provided, if not use the default
sdl_path="${1:-$default_sdl_path}"
lib_file_type="${2:-'so'}"
if [ "$lib_file_type" = "dll" ]; then
    lib_file_name="SDL2"
else
    lib_file_name="libSDL2"
fi
lib_file="$lib_file_name.$lib_file_type"
echo " > sdl path is [$sdl_path] lib file [$lib_file]"

# Set the download URL for SDL2
version="2.30.2"
sdl_url="https://github.com/libsdl-org/SDL/releases/download/release-$version/SDL2-$version.zip"
sdl_zip="build/sdl.zip"
sdl_source="$sdl_path/SDL2-$version" # SDL2-2.0.14"

sdl_include="include/sdl"
sdl_include_source="$sdl_path/include"
sdl_lib_file="lib/$lib_file"
sdl_lib_file_source="$sdl_path/build/.libs/$lib_file"
sdl_lib_file2="lib/libSDL2-2.0.$lib_file_type.0"
sdl_lib_file_source2="$sdl_path/build/.libs/libSDL2-2.0.$lib_file_type.0"

# download sdl2
if [ -d $sdl_path ]; then
    echo " > sdl source detected [$sdl_path]"
else
    echo " + downloading sdl source from [$sdl_url]"
    wget -O "$sdl_zip" "$sdl_url" > /dev/null 2>&1
    echo " + unzipping [$sdl_path]"
    unzip -q "$sdl_zip" -d "$sdl_path" > /dev/null 2>&1
    echo " + deleting zip [$sdl_zip]"
    rm "$sdl_zip"
    # remove folder build/sdl/SDL2-2.0.14
    mv "$sdl_source"/* "$sdl_path"
    rmdir "$sdl_source"
fi

if [ -f $sdl_lib_file ]; then
    echo " > sdl lib detected [$sdl_lib_file]"
else
    # remove folder build/sdl/SDL2-2.0.14
    if [ -f $sdl_path/$lib_file ]; then
        echo " > lib file detected [$sdl_path/$lib_file]"
    else
        echo " + building [$lib_file]"
        if [ -f $sdl_lib_file_source ]; then
            echo " > [$sdl_lib_file_source] already made"
        else
            cd $sdl_path
            echo " > cleaning source of sdl"
            make clean > /dev/null 2>&1
            echo " > configuring sdl"
            ./autogen.sh > /dev/null 2>&1
            if [ "$lib_file_type" = "dll" ]; then
                echo "   - configuring for mingw32"
                ./configure --host=x86_64-w64-mingw32 --enable-shared --disable-static # > /dev/null 2>&1
            else
                ./configure --enable-shared --disable-static > /dev/null 2>&1
            fi
            if [ $? -ne 0 ]; then
                echo " ! sdl configure failed"
                exit
            else
                echo " + configure successful"
            fi
            echo " > making sdl"
            make > /dev/null 2>&1
            if [ $? -ne 0 ]; then
                echo " ! sdl make failed"
                exit
            else
                echo " + make successful"
            fi
            cd ../..
        fi
    fi
    if [ ! -f $sdl_lib_file_source ]; then
        echo " ! failed to make [$sdl_lib_file_source]"
    else
        echo " + copying to [$sdl_lib_file]"
        cp $sdl_lib_file_source $sdl_lib_file
    fi
fi

# if linux, copy lib.so.0 file
if [ ! "$lib_file_type" == "dll" ]; then
    if [ ! -f $sdl_lib_file2 ]; then
        echo " + copying to [$sdl_lib_file2]"
        cp $sdl_lib_file_source2 $sdl_lib_file2
    fi
fi

if [ ! -d $sdl_include ]; then
    echo " + creating [$sdl_include]"
    mkdir $sdl_include
    mv $sdl_include_source/* $sdl_include
else
    echo " > sdl include detected [$sdl_include]"
fi

echo " ====== ====== ====== ====== ====== ======"
