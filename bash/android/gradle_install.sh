#!/bin/bash

# apk_filepath="build/android-build/app/build/outputs/apk/release/app-release-unsigned.apk"
apk_filepath="build/android-build/app/build/outputs/apk/release/zoxel.apk"
echo "  > installing android release build at [$apk_filepath]"
adb install $apk_filepath