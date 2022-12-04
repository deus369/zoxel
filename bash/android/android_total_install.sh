#!/bin/bash

# remove last zoxel-android

current_directory="$HOME/zoxel/bash/android"

# todo: install SDL folders into a directory with bash

echo "Reinstalling Android builder from $current_directory"

rm -R $HOME/zoxel-android

cd $current_directory

source android_copy_android_project.sh

cd $current_directory

source android_copy_sdl.sh

cd $current_directory

source android_copy_source.sh

cd $current_directory

source gradle_install_debug.sh

echo Finished installing files

sleep 30
