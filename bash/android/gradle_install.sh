#!/bin/bash

export ANDROID_SDK_ROOT=/usr/lib/android-sdk
# source bash/android/gradle_set_paths.sh
# cd $android_directory
cd build/android-build
# ./gradlew install #installRelease
# echo ""
echo "  > building android release build"
# echo "-----"
bash gradlew build --parallel && bash gradlew install --parallel

# echo ""
# echo "gradlew installRelease"
# echo "-----"
# bash gradlew install --parallel # --debug  --stacktrace

# echo ""
# echo "Installing unsigned release build."
# echo "-----"
# adb install $android_directory/app/build/outputs/apk/release/app-release-unsigned.apk

# echo ""

# echo ""
# echo Finished Installing Release Zoxel Android
# echo ""