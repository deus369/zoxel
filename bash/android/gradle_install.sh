#!/bin/bash

source bash/android/gradle_set_paths.sh
cd $android_directory
# ./gradlew install #installRelease
echo ""
echo "Building android release build."
echo "-----"
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