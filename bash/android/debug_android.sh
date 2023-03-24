#!/bin/bash

log_tag="Zoxel"
package_name="org.mrpenguin.zoxel"
echo "  > debugging zoxel android [$log_tag]."
while true; do
    # adb logcat *:V # $package_name *:V
    # adb logcat $package_name Zoxel:V
    # adb logcat $log_tag:verbose *:V
    # adb logcat
    # adb logcat $log_tag:verbose *:S
    # adb logcat -s "$log_tag"
    adb logcat -s SDL
    sleep 1
    # echo "Restarting logcat."
done

echo "  > finished debugging zoxel android"

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
