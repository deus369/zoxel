#!/bin/bash
source bash/android/gradle_pathing.sh
clear_gradle_build
start_gradle_build
# adb=$ANDROID_SDK_ROOT/platform-tools/adb
echo " > debugging zoxel android [$log_tag]"
$ANDROID_SDK_ROOT/platform-tools/adb shell am start -n "$package_name/.$activity_name"
while true; do
    echo "   > logcat [$log_tag:V]"
    # useful
    # $adb logcat -s SDL
    $adb logcat $log_tag:verbose *:S
    # $adb logcat | grep $log_tag
    # $adb logcat -s $log_tag:V
    sleep 1
done
echo " > finished debugging zoxel android"
end_gradle_build
