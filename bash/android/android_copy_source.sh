#!/bin/bash

# \todo Also copy files:
#   - app/jni/CMakeLists.txt
#   - app/jni/CMakeLists.txt
#   - app/jni/src/Android.mk
#   - app/src/main/AndroidManifest.xml
#   - app/src/main/res
#   - resources into app/src/main/resources/ & rename to android-resources sub folder

source gradle_set_paths.sh

new_source_directory0=$android_directory/app/jni/src

old_source_directory1=$zoxel_directory/src
old_source_directory2=$zoxel_directory/include

new_source_directory1=$new_source_directory0/src
new_source_directory2=$new_source_directory0/include


# first remove source files from new directory
echo Removing $new_source_directory1
rm -R $new_source_directory1
echo Removing $new_source_directory2
rm -R $new_source_directory2

# next copy all source files over
echo Copying $old_source_directory1 to $new_source_directory1
cp -R $old_source_directory1 $new_source_directory1

echo Copying $old_source_directory2 to $new_source_directory2
cp -R $old_source_directory2 $new_source_directory2

echo Finished copying source files
# sleep 2
# echo Make sure to set AndroidBuild in include file at $new_source_directory0/src
# sleep 1
