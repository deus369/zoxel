#!/bin/bash

source gradle_set_paths.sh

cd $android_directory

# ./gradlew install #installRelease

echo ""
echo "Building android release build."
echo "-----"
./gradlew build --parallel

# echo ""
# echo "Installing unsigned release build."
# echo "-----"
# adb install $android_directory/app/build/outputs/apk/release/app-release-unsigned.apk

echo ""
echo "gradlew installRelease"
echo "-----"
./gradlew install --parallel # --debug  --stacktrace

echo ""
echo Finished Installing Release Zoxel Android
echo ""