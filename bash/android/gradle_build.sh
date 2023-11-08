#!/bin/bash

echo "=> gradle building android release build"


android_sdk_path="$HOME/android_sdk"
ndk_path="$android_sdk_path/ndk"
export ANDROID_HOME=$android_sdk_path
export ANDROID_SDK_ROOT=$android_sdk_path
export ANDROID_NDK_HOME=$ndk_path

# export ANDROID_SDK_ROOT=/usr/lib/android-sdk

cd build/android-build
bash gradlew assembleRelease # --parallel
cd ../..
