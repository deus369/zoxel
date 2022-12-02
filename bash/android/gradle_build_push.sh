#!/bin/bash

zoxel_directory="$HOME/zoxel"
sdl_directory="$HOME/projects/SDL"
ANDROID_NDK_HOME="$HOME/android/android-ndk-r10e"
export ANDROID_NDK_HOME="$HOME/android/android-ndk-r10e"
ANDROID_HOME="/usr/lib/android-sdk"
ANDROID_SDK_ROOT="/usr/lib/android-sdk"
export ANDROID_HOME="/usr/lib/android-sdk"
export ANDROID_SDK_ROOT="/usr/lib/android-sdk"

cd ~/projects/android-project/

./gradlew installDebug

echo Finished Building Zoxel Android
sleep 330
