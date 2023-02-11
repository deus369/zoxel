#!/bin/bash

# remove last zoxel-android
zoxel_directory="$HOME/zoxel"
cd $zoxel_directory/bash/android
source gradle_set_paths.sh

source update_android_build.sh

# install on android device
echo "Installing zoxel android using gradle."
cd $android_bash_directory
source gradle_install_debug.sh

echo Finished installing android debug build.