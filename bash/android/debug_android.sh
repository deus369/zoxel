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

# adb logcat -s "$log_tag" color *:V
# adb logcat *:V # $package_name *:V
# adb logcat $package_name Zoxel:V
# adb logcat $log_tag:verbose *:V
# adb logcat
# adb logcat $log_tag:verbose *:S
# adb logcat -s SDL
# adb logcat -v color *:V
# sleep 333
# adb logcat | grep -F "`adb shell ps | grep com.zoxel.zoxel  | tr -s [:space:] ' ' | cut -d' ' -f2`" |
# verbose, info, debug
# https://stackoverflow.com/questions/27108851/logcat-difference-between-log-levels
# adb -d logcat org.libsdl.app:verbose *:S
# adb logcat org.libsdl.app:verbose *:S
# adb logcat | grep -F "`adb shell ps | grep org.libsdl.app  | tr -s [:space:] ' ' | cut -d' ' -f2`"
# adb -d logcat org.libsdl.app:info *
# adb logcat --pid=`adb shell pidof -s org.libsdl.app`
# adb logcat | grep org.libsdl.app
# pid=$(adb shell ps | grep $package_name | cut -c11-15) ; adb logcat | grep $pid

# $adb logcat -s $package_name
# $adb logcat -s $log_tag color
# $adb logcat
# $adb logcat | grep "error"
# $adb logcat | grep $package_name
# $adb logcat -s $activity_name
# $adb logcat -s $log_tag
# $adb logcat | grep "zoxel"
# $adb logcat | grep "asset directory is null"
