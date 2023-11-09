#!/bin/bash

echo "  > gradle pathing check"
pathing_locker_id=-1
pathing_locker="/tmp/zox_gradle_building.lock"

clear_gradle_build() {
    echo "  > clearing gradle pathing lock"
    rm "$pathing_locker"
}

# Function to start the Gradle build
start_gradle_build() {
    # Check if the lock file exists
    if [ -f "$pathing_locker" ]; then
        return 1
    fi
    # Create the lock file
    pathing_locker_id=$PPID
    touch "$pathing_locker"
    echo "  > gradle setting paths"
    zoxel_directory=$PWD
    android_sdk_path="$zoxel_directory/build/android_sdk"
    ndk_path="$android_sdk_path/ndk"
    export ANDROID_HOME=$android_sdk_path
    export ANDROID_SDK_ROOT=$android_sdk_path
    export ANDROID_NDK_HOME=$ndk_path
    # export zoxel_directory="$zoxel_directory"
    android_directory="$zoxel_directory/build/android-build"
    android_bash_directory="$zoxel_directory/bash/android"
    # export JAVA_HOME="/usr/lib/jvm/java-17-openjdk/bin/java"
    export JAVA_HOME="/usr/lib/jvm/java-17-openjdk" # $(dirname $(dirname $(whereis java)))
    # SDL
    sdl_directory="$zoxel_directory/build/sdl/sdl" # "$HOME/SDL/SDL2"
    export sdl_directory="$zoxel_directory/build/sdl/sdl" # "$HOME/SDL/SDL2"
    sdl_android_project_directory="$sdl_directory/android-project"
    sdl_image_directory="$zoxel_directory/build/sdl/sdl_image"  # $HOME/SDL/SDL2_image
    sdl_mixer_directory="$zoxel_directory/build/sdl/sdl_mixer"  # $HOME/SDL/SDL2_mixer
    # print paths
    echo "      + zoxel_directory is $zoxel_directory"
    echo "      + android sdk path to [$ANDROID_SDK_ROOT]"
    echo "      + ndk path to [$ANDROID_NDK_HOME]"
    echo "      + java path is [$JAVA_HOME]"
    echo "      + android_directory [$android_directory]"
    echo "      + android_bash_directory [$android_bash_directory]"
    echo "      + sdl_android_project_directory [$sdl_android_project_directory]"
    echo "      + sdl_directory [$sdl_directory]"
    echo "      + sdl_image_directory [$sdl_image_directory]"
    echo "      + sdl_mixer_directory [$sdl_mixer_directory]"
    return 0
}

# Function to end the Gradle build
end_gradle_build() {
    #if [ -f "$pathing_locker" ]; then
    if [ pathing_locker_id -eq $PPID ]; then
        clear_gradle_build
    fi
}

# Example usage:
# Call start_gradle_build at the beginning of your build process
# Call end_gradle_build at the end of your build process

# Example:
# start_gradle_build

# Your Gradle build commands go here

# end_gradle_build


# export PATH=$PATH:$ANDROID_HOME # /bin
# export PATH=$PATH:$ANDROID_NDK_HOME
# echo "Set path to $PATH"

# ndk installation path
# android_sdk_directory=$zoxel_directory/build/android # "$HOME/android"
# ANDROID_NDK_HOME="$android_sdk_directory/ndk"
# export ANDROID_NDK_HOME="$android_sdk_directory/ndk"
# # Android installation path
# ANDROID_HOME="$android_sdk_directory/sdk" # "/usr/lib/android-sdk"
# export ANDROID_HOME="$android_sdk_directory/sdk" # "/usr/lib/android-sdk"
# ANDROID_SDK_ROOT="$ANDROID_HOME" # "/usr/lib/android-sdk"
# export ANDROID_SDK_ROOT="$ANDROID_HOME" #"/usr/lib/android-sdk"
