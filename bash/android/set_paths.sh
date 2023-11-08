#!/bin/bash

zoxel_directory=$PWD
android_sdk_path="$HOME/android_sdk"
ndk_path="$android_sdk_path/ndk"
export ANDROID_HOME=$android_sdk_path
export ANDROID_SDK_ROOT=$android_sdk_path
export ANDROID_NDK_HOME=$ndk_path
export PATH=$PATH:$ANDROID_HOME # /bin
export PATH=$PATH:$ANDROID_NDK_HOME

echo "zoxel_directory is $zoxel_directory"
echo "Set sdk path to $ANDROID_HOME"
echo "Set ndk path to $ANDROID_NDK_HOME"
echo "Set path to $PATH"

# sdk_install_directory="$zoxel_directory/build/android/sdk"
# ndk_install_directory="$zoxel_directory/build/android/ndk"
# export ANDROID_HOME=$sdk_install_directory/cmdline-tools/latest
# export ANDROID_NDK_HOME=$ndk_install_directory # /android-ndk-r23
