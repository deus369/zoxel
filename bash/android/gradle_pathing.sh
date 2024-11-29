#!/bin/bash

source bash/android/_core.sh

# global variables
is_sdl_image=true
is_sdl_mixer=true
# echo "  > gradle pathing check"
pathing_locker_id=0
pathing_locker="/tmp/zox_gradle_building.lock"

clear_gradle_build() {
    # echo "  > clearing gradle pathing lock"
    if [ -f "$pathing_locker" ]; then
        rm "$pathing_locker"
    fi
}

# Function to start the Gradle build
start_gradle_build() {
    if [ -z "$sdl_directory" ]; then
        # echo " > clearing gradle as failed to clear last run"
        clear_gradle_build
    fi
    # Check if the lock file exists
    if [ -f "$pathing_locker" ]; then
        return 1
    fi
    # Create the lock file
    pathing_locker_id=$PPID
    touch "$pathing_locker"
    # global variables
    ndk_ver=25 # 15c / 13b / 21 / 26b
    # jdk_ver=20 # 7 / 11 / 20
    #jdk_ver=$(java --version 2>&1 | grep openjdk | awk '{split($2, a, "."); print a[1]}')
    #echo " > JDK Version found [$jdk_ver]"
    platform_ver=34 # 30
    platform_tools_ver=34.0.5
    build_tools_ver=34.0.0 # -rc4 # 30.0.3
    # echo "  > gradle setting paths"
    zoxel_directory=$PWD
    android_sdk_path="$zoxel_directory/build/android_sdk"
    apksigner=$android_sdk_path/build-tools/$build_tools_ver/apksigner
    if [ is_windows ]; then
        apksigner="$apksigner.bat"
    fi
    echo "apksigner is at [$apksigner]"
    ndk_path=$android_sdk_path/ndk
    export ANDROID_HOME=$android_sdk_path
    export ANDROID_SDK_ROOT=$android_sdk_path
    export ANDROID_NDK_HOME=$ndk_path
    # export zoxel_directory="$zoxel_directory"
    android_directory=$zoxel_directory/build/android-build
    android_build_directory=$zoxel_directory/build/android-build
    android_bash_directory=$zoxel_directory/bash/android
    # export JAVA_HOME="/usr/lib/jvm/java-17-openjdk/bin/java"
    # Get the result of 'whereis jdk'
    # jdk_whereis=$(whereis java) # locates jdk through whereis
    # jdk_whereis2=$(echo $jdk_whereis | awk '{print $NF}') # gets the last string in the list
    # jdk_whereis2=$(dirname "$(dirname "$jdk_whereis2")")
    # JAVA_HOME=$jdk_whereis2 #"/usr/lib/jvm/java-17-openjdk"
    #JAVA_HOME=/usr/lib/jvm/java-$jdk_ver-openjdk # 7 / 11 / 20
    #export JAVA_HOME=$JAVA_HOME
    # javaHome=$JAVA_HOME # "/usr/lib/jvm/java-17-openjdk" # $(dirname $(dirname $(whereis java)))
    source bash/android/_core.sh
    #if [ ! is_windows ]; then
    source bash/android/set_java_home.sh
    #fi
    # SDL
    sdl_parent_directory=$zoxel_directory/build/android-sdl
    sdl_directory=$sdl_parent_directory/sdl
    export sdl_directory=$sdl_parent_directory/sdl
    sdl_android_project_directory=$sdl_directory/android-project
    sdl_image_directory=$sdl_parent_directory/sdl_image
    sdl_mixer_directory=$sdl_parent_directory/sdl_mixer
    # tools
    apk_filepath="build/android-build/app/build/outputs/apk/release/zoxel.apk"
    adb=$android_sdk_path/platform-tools/adb
    package_name="org.libsdl.app"
    activity_name="SDLActivity"
    log_tag="Zoxel"
    # print paths
    # echo "      + zoxel_directory is $zoxel_directory"
    # echo "      + android_directory [$android_directory]"
    # echo "      + android_bash_directory [$android_bash_directory]"
    # echo "      + sdl_android_project_directory [$sdl_android_project_directory]"
    # echo "      + sdl_directory [$sdl_directory]"
    # echo "      + sdl_image_directory [$sdl_image_directory]"
    # echo "      + sdl_mixer_directory [$sdl_mixer_directory]"
    # echo "      + android sdk path to [$ANDROID_SDK_ROOT]"
    # echo "      + ndk path to [$ANDROID_NDK_HOME]"
    # echo "      + java path is [$JAVA_HOME]"
    return 0
}

# Function to end the Gradle build
end_gradle_build() {
    #if [ -f "$pathing_locker" ]; then
    if [ $pathing_locker_id -eq $PPID ]; then
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

# $ANDROID_SDK_ROOT/platform-tools/adb
