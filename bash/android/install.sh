#!/bin/bash

# write a script to download sdl2 folders
# do a check for SDL/SDL2 SDL/SDL_image SDL/SDL_mixer directories

# remove last zoxel-android
cd $HOME/zoxel/bash/android
source gradle_set_paths.sh

source update_android_build.sh

# install on android device
echo "Installing zoxel android using gradle."
cd $android_bash_directory
source gradle_install_release.sh

echo Finished installing android build.