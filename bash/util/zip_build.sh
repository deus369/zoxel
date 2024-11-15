#!/bin/bash
architecture=$(uname -m | tr '[:upper:]' '[:lower:]')    # Determine the system architecture
#os_type=$(uname -s | tr '[:upper:]' '[:lower:]')    # Determine the operating system type
os_type=$(uname | cut -c1-5 | tr '[:upper:]' '[:lower:]')
if [ $os_type == "mingw" ]; then
    os_type="windows"
fi
zip_name="zoxel_${os_type}_${architecture}.zip"
zip_path="build/$zip_name"
#cd build
if [ -f $zip_path ]; then
    echo "  - removing old zip file [$zip_path]"
    rm -f $zip_path
    sleep 1
else
    echo " + first time building zip [$zip_path]"
fi
target_executable="$1"
build_directory="$(dirname $target_executable)"
target_filename="$(file $target_executable)"
echo " > using target_executable [$target_executable]"
echo " > using build_directory: [$build_directory]"
echo " > using target_filename [$target_filename]"
echo " + creating zip [$zip_path]"

if [ -d $build_directory ]; then
    echo " + zipping [$build_directory]"
    zip -j "$zip_path" $build_directory/*
    zip -r "$zip_path" resources
else
    echo " ! [$build_directory] not found"
fi

if [ -d ../zoxel-web ]; then
    echo " + found zoxel-web directory"
    echo " + copied [$zip_path] into [../zoxel-web/builds/$zip_name]"
    cp -f $zip_path ../zoxel-web/builds/$zip_name
else
    echo " ! failed finding ../zoxel-web"
fi
