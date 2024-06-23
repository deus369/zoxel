#!/bin/bash

echo " > installing glew from source"
# Default output parameter
default_glew_path="build/glew"
# Check if an argument is provided, if not use the default
glew_path="${1:-$default_glew_path}"
lib_file_type="${2:-'a'}"
echo " > glew path is [$glew_path] filetype [$lib_file_type]"
glew_url="https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip"
glew_zip="build/glew.zip"
glew_source="$glew_path/glew-2.2.0"
glew_lib_file="lib/libGLEW.$lib_file_type"
glew_include="include/glew"
glew_include_source="$glew_path/include/GL"

# Download glew source
if [ ! -d $glew_path ]; then
    echo " + downloading glew from [$glew_url]"
    wget -O "$glew_zip" "$glew_url"
    unzip -q "$glew_zip" -d "$glew_path"
    rm "$glew_zip"
    # remove folder build/glew/glew-2.2.0
    mv "$glew_source"/* "$glew_path"
    rmdir "$glew_source"
fi

if [ -f $glew_lib_file ]; then
    echo " > glew lib detected [$glew_lib_file]"
else
    if [ ! -f "$glew_path/lib/libGLEW.$lib_file_type" ]; then
        cp bash/glew/Makefile_dll build/glew/Makefile_dll
        echo " + building [libGLEW.$lib_file_type]"
        cd $glew_path
        if [[ $lib_file_type -eq "dll" ]]; then
            echo " + building for windows mingw"
            #make -f Makefile.mingw clean
            #make -f Makefile_dll
            make SYSTEM=mingw # CC=x86_64-w64-mingw32-gcc
        else
            make clean
            make
        fi
        cd ../.. # return to zoxel
    fi
    echo " + copying to [$glew_lib_file]"
    cp "$glew_path/lib/libGLEW.$lib_file_type" $glew_lib_file
fi

if [ ! -d $glew_include ]; then
    echo " + creating [$glew_include]"
    mkdir $glew_include
    mv $glew_include_source/* $glew_include
else
    echo " > glew include detected [$glew_include]"
fi
