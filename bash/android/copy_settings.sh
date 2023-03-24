#!/bin/bash

# \todo Also copy files:
#   - app/jni/CMakeLists.txt
#   - app/jni/CMakeLists.txt
#   - app/jni/src/Android.mk
#   - app/src/main/AndroidManifest.xml
#   - app/src/main/res
#   - resources into app/src/main/resources/ & rename to android-resources sub folder

source $PWD/bash/android/gradle_set_paths.sh

# new_source_directory0=$android_directory/app/jni/src
# # our settings files
# old_source_directory1=$android_bash_directory/src
# old_source_directory2=$zoxel_directory/include

# our new locations
# old_source_file1=$zoxel_directory/Android.mk
# old_source_file2=$zoxel_directory/CMakeLists.txt
# new_source_file1=$new_source_directory0/Android.mk
# new_source_file2=$new_source_directory0/CMakeLists.txt

# copy settings files over

# copy manifesto
android_manifesto_file=$android_bash_directory/app/src/main/AndroidManifest.xml
android_manifesto_file_target=$android_directory/app/src/main/AndroidManifest.xml
echo Copying $android_manifesto_file to $android_manifesto_file_target
rm $android_manifesto_file_target
cp $android_manifesto_file $android_manifesto_file_target

# copy res folder
android_res_directory=$android_bash_directory/app/src/main/res
android_res_directory_target=$android_directory/app/src/main/res
echo Copying $android_res_directory to $android_res_directory_target
rm -R $android_res_directory_target
cp -R $android_res_directory $android_res_directory_target

# copy Application.mk, CMakeLists.txt, src/Android.mk
jni_directory=$android_bash_directory/app/jni
jni_directory_target=$android_directory/app/jni

file_1_name=Application.mk
file_1=$jni_directory/$file_1_name
file_1_target=$jni_directory_target/$file_1_name
echo Copying $file_1 to $file_1_target
rm $file_1_target
cp $file_1 $file_1_target

file_2_name=CMakeLists.txt
file_2=$jni_directory/$file_2_name
file_2_target=$jni_directory_target/$file_2_name
echo Copying $file_2 to $file_2_target
rm $file_2_target
cp $file_2 $file_2_target

file_3_name=src/Android.mk
file_3=$jni_directory/$file_3_name
file_3_target=$jni_directory_target/$file_3_name
echo Copying $file_3 to $file_3_target
rm $file_3_target
cp $file_3 $file_3_target

echo "Finished copying settings files."
# sleep 3