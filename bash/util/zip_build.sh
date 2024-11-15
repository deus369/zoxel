#!/bin/bash
architecture=$(uname -m | tr '[:upper:]' '[:lower:]')    # Determine the system architecture
#os_type=$(uname -s | tr '[:upper:]' '[:lower:]')    # Determine the operating system type
os_type=$(uname | cut -c1-5 | tr '[:upper:]' '[:lower:]')
if [ $os_type == "mingw" ]; then
    os_type="windows"
fi
zip_name="build/zoxel_${os_type}_${architecture}.zip"
#cd build
if [[ -f $zip_name ]]; then
    echo "  - removing old zip file [$zip_name]"
    rm $zip_name
fi
target_executable="$1"
build_directory="$(dirname $target_executable)"
echo " > using target_executable [$target_executable]"
echo " > using build_directory: [$build_directory]"
echo "  > creating [$zip_name] in build directory"
cd $build_directory && zip -r "$zip_name" resources
cd $build_directory/lib && zip -r "$zip_name" /*
zip -j "$zip_name" $target_executable

if [ -z ../../zoxel-web ]; then
    echo " + found zoxel-web directory"
    echo " + copied zip into it"
    cp -f $zip_name ../../zoxel-web/$zip_name
fi

#c#d .. # incase i use this in zoxel directory
