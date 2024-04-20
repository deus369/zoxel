#!/bin/bash

# \todo Also copy files:
#   - app/jni/CMakeLists.txt
#   - app/jni/CMakeLists.txt
#   - app/jni/src/Android.mk
#   - app/src/main/AndroidManifest.xml
#   - app/src/main/res
#   - resources into app/src/main/resources/ & rename to android-resources sub folder
# todo: copy resources into app/src/main/resources/
# ? & rename to android-resources sub folder

source bash/android/gradle_pathing.sh
start_gradle_build

echo "=> copying source files to android project"
new_source_directory0=$android_directory/app/jni/src
old_source_directory1=$zoxel_directory/src
old_source_directory2=$zoxel_directory/include
new_source_directory1=$new_source_directory0/src
new_source_directory2=$new_source_directory0/include
source_directory_resources=$zoxel_directory/resources
target_directory_assets=$android_directory/app/src/main/assets
target_directory_resources=$android_directory/app/src/main/assets/resources

# first remove source files from new directory
echo "  > removing [$new_source_directory1]"
rm -R $new_source_directory1
echo "  > removing [$new_source_directory2]"
rm -R $new_source_directory2
# next copy all source files over
echo "  > copying [$old_source_directory1] to [$new_source_directory1]"
cp -R $old_source_directory1 $new_source_directory1
echo "  > copying [$old_source_directory2] to [$new_source_directory2]"
cp -R $old_source_directory2 $new_source_directory2

if [ ! -d $target_directory_assets ]; then
    echo "  > creating [$$target_directory_assets]"
    mkdir $target_directory_assets
fi
if [ -d $target_directory_resources ]; then
    echo "  > removing [$target_directory_resources]"
    rm -R $target_directory_resources
fi
# echo "  > copying [$source_directory_resources] to [$target_directory_resources]"
cp -R $source_directory_resources $target_directory_resources

end_gradle_build
