#!/bin/bash

zoxel_directory="$HOME/zoxel"
sdl_directory="$HOME/projects/SDL2"

# copy android-project to home directory

cp -R $sdl_directory/android-project $HOME

mv $HOME/android-project $HOME/zoxel-android

echo "FInished copying to home."

sleep 30
