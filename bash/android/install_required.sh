#!/bin/bash
# installs all the requirements for an android build on linux x86

sudo apt-get install default-jdk
bash bash/android/install_android_sdk.sh
bash bash/android/install_android_ndk.sh
bash bash/android/install_sdl.sh
source $PWD/bash/android/android_copy_settings.sh
source $PWD/bash/android/android_copy_sdl.sh
source $PWD/bash/android/android_copy_source.sh
# will this update gradle? or do I need installDebug as input
source $PWD/bash/android/gradle_set_paths.sh
bash $android_directory/gradlew

# install sdl2 sdl2_image and sdl2_mixer into projects from git
# install android sdk and ndk into projects or something
# then copy android sdl project into /build/android
# next copy source over
# gradle push to phone after
# check if android sdk/ndk installed, if not install:
#   > bash install_android_sdk.sh && bash install_android_ndk.sh