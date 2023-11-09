#!/bin/bash
source bash/android/gradle_pathing.sh
start_gradle_build
# apk_filepath="build/android-build/app/build/outputs/apk/release/app-release-unsigned.apk"
apk_filepath="build/android-build/app/build/outputs/apk/release/zoxel.apk"
echo "  > installing android release build at [$apk_filepath]"
$ANDROID_SDK_ROOT/platform-tools/adb install $apk_filepath

#apk_filepath2="build/android-build/app/build/outputs/apk/release/app-release-unsigned.apk"
#$HOME/android_sdk/platform-tools/adb install $apk_filepath2

end_gradle_build

