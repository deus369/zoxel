#!/bin/bash

zoxel_directory="$HOME/zoxel"
export zoxel_directory="$zoxel_directory"
android_directory="$zoxel_directory/android-build"
android_bash_directory="$zoxel_directory/bash/android"

# ndk installation path
android_sdk_directory="$HOME/android"
ANDROID_NDK_HOME="$android_sdk_directory/ndk"
export ANDROID_NDK_HOME="$android_sdk_directory/ndk"

# Android installation path
ANDROID_HOME="/usr/lib/android-sdk"
export ANDROID_HOME="/usr/lib/android-sdk"
ANDROID_SDK_ROOT="/usr/lib/android-sdk"
export ANDROID_SDK_ROOT="/usr/lib/android-sdk"

# SDL
sdl_directory="$HOME/SDL/SDL2"
export sdl_directory="$HOME/SDL/SDL2"
sdl_image_directory=$HOME/SDL/SDL2_image
sdl_mixer_directory=$HOME/SDL/SDL2_mixer
sdl_android_project_directory="$sdl_directory/android-project"