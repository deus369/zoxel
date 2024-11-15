#!/bin/bash
architecture=$(uname -m | tr '[:upper:]' '[:lower:]')    # Determine the system architecture
os_type=$(uname -s | tr '[:upper:]' '[:lower:]')    # Determine the operating system type
zip_name="zoxel_${os_type}_${architecture}.zip"
cd build
if [[ -f $zip_name ]]; then
    echo "  - removing old zip file [$zip_name]"
    rm $zip_name
fi
echo "  > creating [$zip_name] in build directory"
zip -r "$zip_name" resources
zip -r "$zip_name" lib/*
zip -j "$zip_name" zoxel

if [ -z ../../zoxel-web ]; then
    echo " + found zoxel-web directory"
    echo " + copied zip into it"
    cp -f $zip_name ../../zoxel-web/$zip_name
fi

cd .. # incase i use this in zoxel directory
