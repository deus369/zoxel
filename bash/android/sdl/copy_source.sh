#!/bin/bash

# Also copy files:
#   - app/jni/CMakeLists.txt
#   - app/jni/CMakeLists.txt
#   - app/jni/src/Android.mk
#   - app/src/main/AndroidManifest.xml
#   - app/src/main/res
#   - resources into app/src/main/resources/ & rename to android-resources sub folder
# copy resources into app/src/main/resources/
# ? & rename to android-resources sub folder

source bash/android/gradle_pathing.sh
start_gradle_build
source bash/util/verbose_echo.sh
# verbose_level=0

echo "=> copying source files to android project"
new_source_directory0=$android_directory/app/jni/src
old_source_directory1=$zoxel_directory/src
new_source_directory1=$new_source_directory0/src
include_source=$zoxel_directory/include
include_destination=$new_source_directory0/include
source_directory_resources=$zoxel_directory/resources
target_directory_assets=$android_directory/app/src/main/assets
target_directory_resources=$android_directory/app/src/main/assets/resources

# first remove source files from new directory
echo_2 "  - removing [$new_source_directory1]"
rm -R $new_source_directory1
# next copy all source files over
echo_2 "  - copying [$old_source_directory1] to [$new_source_directory1]"
cp -R $old_source_directory1 $new_source_directory1

# includes just need flecs
echo_2 "  - removing [$include_destination]"
rm -R $include_destination
echo_2 "  - copying [$include_source] to [$include_destination]"
mkdir $include_destination
#cp $include_source/* $include_destination
cp -R $include_source/flecs $include_destination/flecs

if [ ! -d $target_directory_assets ]; then
    echo_2 "  - creating [$$target_directory_assets]"
    mkdir $target_directory_assets
fi
if [ -d $target_directory_resources ]; then
    echo_2 "  - removing [$target_directory_resources]"
    rm -R $target_directory_resources
fi

echo_2 "  - copying [$source_directory_resources] to [$target_directory_resources]"
cp -R $source_directory_resources $target_directory_resources

end_gradle_build
