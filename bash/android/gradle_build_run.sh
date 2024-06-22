#!/bin/bash

source bash/android/gradle_pathing.sh
clear_gradle_build
start_gradle_build

source bash/android/sdl/copy_settings.sh
source bash/android/sdl/copy_source.sh
source bash/android/gradle_build.sh
source bash/android/gradle_sign.sh
source bash/android/gradle_install.sh
source bash/android/gradle_run.sh

end_gradle_build

# echo "  > home is [$HOME]"
# android_sdk_path="$HOME/android_sdk"
# ndk_path="$android_sdk_path/ndk"
# export ANDROID_HOME="$android_sdk_path"
# export ANDROID_SDK_ROOT=$android_sdk_path
# echo "  > android sdk path is $android_sdk_path"
# echo "  > android ndk path is $ndk_path"
