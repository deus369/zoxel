#!/bin/bash

source bash/android/gradle_build.sh

cd build/android-build
echo "  > signing android release build"
echo "need to sign apk: "

apk_filepath="app/build/outputs/apk/release/app-release-unsigned.apk"
# apk_filepath="app/build/outputs/apk/release/zipped.apk"

# sign the apk, i should save the keyname/alias somewhere for later
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore ~/.keys/zoxel.keystore $apk_filepath zoxel

# install the apk
echo "  > installing android release build"
adb install $apk_filepath

# run the apk
echo "  > running android release build"
adb shell am start -n org.libsdl.app/.SDLActivity

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
# export ANDROID_SDK_ROOT=/usr/lib/android-sdk
# source bash/android/gradle_set_paths.sh
# cd $android_directory
# ./gradlew install #installRelease
# echo ""

# echo "-----"
# bash gradlew build --parallel && bash gradlew install --parallel
# bash gradlew installRelease --parallel

# bash gradlew assembleRelease --parallel
