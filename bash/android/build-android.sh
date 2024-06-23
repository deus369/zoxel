#!/bin/bash
# old script? delete this
source bash/android/gradle_pathing.sh
start_gradle_build
cd $zoxel_directory
SRCS="$zoxel_directory/includes/flecs.c $zoxel_directory/src/main.c"
echo Running androidbuild.sh
cd $sdl_directory/build-scripts/
./androidbuild.sh org.zoxel.zoxel $SRCS
echo Running gradlew in org.zoxel.zoxel build folder
cd $sdl_directory/build/org.zoxel.zoxel/
./gradlew installDebug
echo Finished Building Zoxel Android
end_gradle_build

# make -j$(nproc) -f MakefileDev -B; ./zoxel-dev
# cc -std=c99 -fPIC -D_DEFAULT_SOURCE -Wall -g -o zoxel-dev includes/flecs.c src/main.c -lGL -lSDL2 -lm

# sh $sdl_directory/build-scripts/androidbuild.sh org.zoxel.zoxel $SRCS
#zoxel_directory="$HOME/zoxel"
#sdl_directory="$HOME/SDL/SDL2"

# ANDROID_NDK_HOME="$HOME/android/android-ndk-r10e"
# export ANDROID_NDK_HOME="$HOME/android/android-ndk-r10e"
# ANDROID_HOME="/usr/lib/android-sdk"
# ANDROID_SDK_ROOT="/usr/lib/android-sdk"
# export ANDROID_HOME="/usr/lib/android-sdk"
# export ANDROID_SDK_ROOT="/usr/lib/android-sdk"

#android_sdk_path="$HOME/android_sdk"
#ndk_path="$android_sdk_path/ndk"
#export ANDROID_HOME=$android_sdk_path
#export ANDROID_SDK_ROOT=$android_sdk_path
#export ANDROID_NDK_HOME=$ndk_path

# .$sdl_directory/build/org.zoxel.zoxel/gradlew org.zoxel.zoxel $SRCS
