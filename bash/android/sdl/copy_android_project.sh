#!/bin/bash
source bash/android/gradle_pathing.sh
start_gradle_build
echo "$sdl_android_project_directory is being copied to $android_directory"
cp -R $sdl_android_project_directory $android_directory
echo "Finished copying to home."
end_gradle_build
