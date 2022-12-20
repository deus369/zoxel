#!/bin/bash

source gradle_set_paths.sh

# copy android-project to home directory
echo "$sdl_android_project_directory is being copied to $android_directory"
cp -R $sdl_android_project_directory $android_directory
# mv $HOME/android-project $android_directory # $HOME/zoxel-android
echo "Finished copying to home."
sleep 3