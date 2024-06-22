#!/bin/bash

echo " > installing glew from source"
# Default output parameter
default_glew_path="build/glew"
# Check if an argument is provided, if not use the default
glew_path="${1:-$default_glew_path}"
echo " > glew path is [$glew_path]"
glew_url="https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip"
glew_zip="build/glew.zip"
glew_source="$glew_path/glew-2.2.0"
glew_lib_file="lib/libGLEW.a"
glew_include="include/glew"
glew_include_source="$glew_path/include/GL"

if [ -f $glew_lib_file ]; then
    echo " > glew lib detected [$glew_lib_file]"
else
    # Download glew
    if [ ! -d $glew_path ]; then
        echo " + downloading glew from [$glew_url]"
        wget -O "$glew_zip" "$glew_url"
        unzip -q "$glew_zip" -d "$glew_path"
        rm "$glew_zip"
        # remove folder build/glew/glew-2.2.0
        mv "$glew_source"/* "$glew_path"
        rmdir "$glew_source"
    fi
    if [ ! -f $glew_path/lib/libGLEW.a ]; then
        echo " + building [libGLEW.a]"
        cd $glew_path
        make
        cd ../.. # return to zoxel
    fi
    echo " + copying to [$glew_lib_file]"
    cp $glew_path/lib/libGLEW.a $glew_lib_file
fi

if [ ! -d $glew_include ]; then
    echo " + creating [$glew_include]"
    mkdir $glew_include
    mv $glew_include_source/* $glew_include
else
    echo " > glew include detected [$glew_include]"
fi
