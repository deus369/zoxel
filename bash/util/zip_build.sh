#!/bin/bash

# Determine the system architecture
architecture=$(uname -m)

# Determine the operating system type
os_type=$(uname -s | tr '[:upper:]' '[:lower:]')

# Zip the temporary directory
zip_name="zoxel_${os_type}_${architecture}.zip"

# zip -r $zip_name "$temp_dir"
# Zip the build/zoxel file and build/sources directory directly

cd build

if [[ -f $zip_name ]]; then
    echo "  > removing old zip file [$zip_name]"
    rm $zip_name
fi

echo "  > creating [$zip_name] in build directory"
zip -r "$zip_name" resources
zip -j "$zip_name" zoxel

cd .. # incase i use this in zoxel directory