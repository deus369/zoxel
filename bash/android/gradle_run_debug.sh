#!/bin/bash
source bash/android/gradle_pathing.sh
start_gradle_build
cd build/zoxel-android && gradle run; cd ../..
# --debug-jvm
echo Finished Running Debug Zoxel Android
end_gradle_build
