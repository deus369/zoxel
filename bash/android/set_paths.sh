#!/bin/bash

zoxel_directory=$PWD
sdk_install_directory="$zoxel_directory/build/android/sdk"
ndk_install_directory="$zoxel_directory/build/android/ndk"
export ANDROID_HOME=$sdk_install_directory/cmdline-tools/latest
export PATH=$PATH:$ANDROID_HOME # /bin
export ANDROID_NDK_HOME=$ndk_install_directory # /android-ndk-r23
export PATH=$PATH:$ANDROID_NDK_HOME

echo "zoxel_directory is $zoxel_directory"
echo "Set sdk path to $ANDROID_HOME"
echo "Set ndk path to $ANDROID_NDK_HOME"
echo "Set path to $PATH"