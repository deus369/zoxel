#!/bin/bash
# apk_filepath="build/android-build/app/build/outputs/apk/release/app-release-unsigned.apk"
apk_debug_filepath="build/android-build/app/build/outputs/apk/debug/app-debug.apk"
echo "  > zoxel [bash/android/gradle_build_dev.sh] running"
source bash/android/gradle_pathing.sh
start_gradle_build
echo "  > building debug zoxel for android"
cd build/android-build
bash gradlew -s assembleDebug --parallel
if [ $? -ne 0 ]; then
    echo "  > gradlew assembleDebug command failed"
    clear_gradle_build
    exit 1
else
    echo "  > gradlew assembleDebug command was successful"
fi
# bash gradlew installDebug
# bash gradlew runDebug
cd ../..
# bash bash/android/gradle_run.sh
# install dev
# $ANDROID_SDK_ROOT/platform-tools/adb install $apk_filepath
cp $apk_debug_filepath build/zoxel-dev.apk
echo " + zoxel-dev.apk completed"
end_gradle_build
