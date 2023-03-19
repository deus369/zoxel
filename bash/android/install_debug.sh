#!/bin/bash

# remove last zoxel-android
# zoxel_directory="$HOME/zoxel"
# cd $zoxel_directory/bash/android
# source bash/android/gradle_set_paths.sh
source bash/android/update_android_build.sh
# install on android device
# echo "Installing zoxel android using gradle."
# cd $android_bash_directory
source bash/android/gradle_install_debug.sh