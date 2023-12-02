#!/bin/bash
# sdkmanager --list to check ndks
source bash/android/gradle_pathing.sh
clear_gradle_build
start_gradle_build
# ndk_ver="ndk;r13b"
# ndk_ver="ndk;r21"
echo " > android sdk is [$android_sdk_path]"
echo " > installing [ndk;r$ndk_ver]"
sdkmanager --sdk_root=$android_sdk_path --install "ndk;r$ndk_ver"
ls $android_sdk_path/ndk
end_gradle_build
