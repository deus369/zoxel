#!/bin/bash
architecture=$(uname -m | tr '[:upper:]' '[:lower:]')    # Determine the system architecture
#os_type=$(uname -s | tr '[:upper:]' '[:lower:]')    # Determine the operating system type
os_type=$(uname | cut -c1-5 | tr '[:upper:]' '[:lower:]')
if [ $os_type == "mingw" ]; then
    os_type="windows"
fi
zip_name="build/zoxel_${os_type}_${architecture}.zip"
#cd build
if [ -f $zip_name ]; then
    echo "  - removing old zip file [$zip_name]"
    rm -f $zip_name
    sleep 1
else
    echo " + first time building zip [$zip_name]"
fi
target_executable="$1"
build_directory="$(dirname $target_executable)"
target_filename="$(file $target_executable)"
echo " > using target_executable [$target_executable]"
echo " > using build_directory: [$build_directory]"
echo " > using target_filename [$target_filename]"
echo "  > creating [$zip_name] in build directory"

if [ -d $build_directory ]; then
    echo " + zipping [$build_directory]"
    zip -j "$zip_name" $build_directory/*
    zip -r "$zip_name" resources
else
    echo " ! [$build_directory] not found"
fi

if [ -d ../zoxel-web ]; then
    echo " + found zoxel-web directory"
    echo " + copied zip into it"
    cp -f $zip_name ../zoxel-web/$zip_name
else
    echo " ! failed finding ../zoxel-web"
fi

#if [ -f $target_executable ]; then
#    echo " + [$target_executable] zipping"
#    # cd $build_directory && zip -r "$zip_name" $target_filename
#    zip -j "$zip_name" $target_executable
#else
#    echo " ! [$target_executable] not found"
#fi
#if [ -d $build_directory/resources ]; then
#    echo " + [$build_directory/resources] zipping"
#    cd $build_directory && zip -r "$zip_name" resources
#else
#    echo " ! [$build_directory/resources] not found"
#fi
#if [ -d $build_directory/lib ]; then
#    echo " + [$build_directory/lib/*] zipping"
#    cd $build_directory/lib && zip -r "$zip_name" *
#else
#    echo " ! [$build_directory/lib] not found"
#fi
