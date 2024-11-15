#!/bin/bash
source bash/android/gradle_pathing.sh
start_gradle_build
cd $zoxel_directory
SRCS="$zoxel_directory/includes/flecs.c $zoxel_directory/src/main.c"
echo Running androidbuild.sh
cd $sdl_directory/build-scripts/
./androidbuild.sh org.zoxel.zoxel $SRCS
echo Running gradlew in org.zoxel.zoxel build folder
cd $sdl_directory/build/org.zoxel.zoxel/
./gradlew installDebug
echo Finished Building Zoxel Android
end_gradle_build
