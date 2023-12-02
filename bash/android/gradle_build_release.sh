 #!/bin/bash

source bash/android/gradle_pathing.sh
android_build_dir=build/zoxel-android
android_output_path=$android_build_dir/zoxel.apk
apk_filepath="build/android-build/app/build/outputs/apk/release/zoxel.apk"
clear_gradle_build
start_gradle_build

source bash/android/copy_settings.sh
source bash/android/copy_source.sh
source bash/android/gradle_build.sh
source bash/android/gradle_sign.sh

if [ ! -d $android_build_dir ]; then
    echo " > creating android build directory [$android_build_dir]"
    mkdir $android_build_dir
else
    echo " > build directory exists [$android_build_dir]"
fi

if [ -f $apk_filepath ]; then
    echo " > copying output to [$android_output_path]"
    cp  $apk_filepath $android_output_path
else
    echo " > zoxel apk build failed, no apk found at [$apk_filepath]"
fi

end_gradle_build

# echo "  > home is [$HOME]"
# android_sdk_path="$HOME/android_sdk"
# ndk_path="$android_sdk_path/ndk"
# export ANDROID_HOME="$android_sdk_path"
# export ANDROID_SDK_ROOT=$android_sdk_path
# echo "  > android sdk path is $android_sdk_path"
# echo "  > android ndk path is $ndk_path"
