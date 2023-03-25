#!/bin/bash

#source bash/android/update_android_build.sh
source bash/android/copy_source.sh
source bash/android/gradle_build_run.sh

# write a script to download sdl2 folders
# do a check for SDL/SDL2 SDL/SDL_image SDL/SDL_mixer directories
# remove last zoxel-android
# zoxel_directory="$HOME/zoxel"
# echo "Installing Zoxel from zoxel directory [$PWD]"
# zoxel_directory=$PWD
# source bash/android/gradle_set_paths.sh
# install on android device
# echo "Installing zoxel android using gradle."
# echo Finished installing android build.