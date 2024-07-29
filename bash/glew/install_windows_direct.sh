#!/bin/bash

glew_url="https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip"
# Set the directory to extract SDL2 to
glew_zip="build/glew.zip"
glew_source="build/glew/glew-2.2.0"
glew_path="build/glew"
dll_source="build/glew/bin/Release/x64/glew32.dll"
dll_destination="lib/glew32.dll"

if [ ! -d $glew_path ]; then
    # Create the directory if it doesn't exist
    mkdir -p "$glew_path"
    # Download SDL2 zip file
    wget -O "$glew_zip" "$glew_url"
    # Extract SDL2 zip file to the C drive
    unzip -q "$glew_zip" -d "$glew_path"
    # Clean up temporary files
    rm "$glew_zip"
    # remove folder build/glew/glew-2.2.0
    mv "$glew_source"/* "$glew_path"
    rmdir "$glew_source"
    # remove folder build/glew/include/GL
    glew_source2="build/glew/include/GL"
    glew_dest2="build/glew/include"
    mv "$glew_source2"/* "$glew_dest2"
    rmdir "$glew_source2"
else
    echo " > [$glew_path] exists"
fi

if [ ! -f $dll_destination ]; then
    cp $dll_source $dll_destination
else
    echo " > [$dll_destination] already exists"
fi
