#!/bin/bash
echo "=> cleaning android sdk"
source bash/android/gradle_pathing.sh
start_gradle_build
echo " > cleaning android-sdk [$android_sdk_path]"
rm -R $android_sdk_path
echo " > cleaning sdl source [$sdl_parent_directory]"
rm -R $sdl_parent_directory
echo " > cleaning android-build [$android_build_directory]"
rm -R $android_build_directory
end_gradle_build
