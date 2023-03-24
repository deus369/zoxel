#!/bin/bash

current_directory=$(pwd)

echo "Inside Zoxel Directory [$current_directory]"

source $PWD/bash/android/copy_source.sh

source $PWD/bash/android/gradle_install_debug.sh

echo Running logcat

cd $current_directory

source $PWD/bash/android/debug_android.sh

echo Finished running latest