#!/bin/bash

source $PWD/bash/android/gradle_set_paths.sh

# copy android-project to home directory
echo "$sdl_android_project_directory is being copied to $android_directory"
cp -R $sdl_android_project_directory $android_directory
echo "Finished copying to home."