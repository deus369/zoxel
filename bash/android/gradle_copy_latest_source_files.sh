#!/bin/bash

android_directory=$HOME/projects/android-project
zoxel_directory=$HOME/zoxel
# push latest source files to android-project directory

old_source_directory1=$zoxel_directory/src
old_source_directory2=$zoxel_directory/includes

new_source_directory1=$android_directory/app/jni/src/src
new_source_directory2=$android_directory/app/jni/src/includes

# first remove source files from new directory
echo Removing $new_source_directory1
sleep 3
rm -R $new_source_directory1
echo Removing $new_source_directory2
sleep 3
rm -R $new_source_directory2

# next copy all source files over
echo Copying $old_source_directory1 to $new_source_directory1
sleep 3
cp -R $old_source_directory1 $new_source_directory1
cp -R $old_source_directory2 $new_source_directory2

echo Finished copying source files
sleep 30
