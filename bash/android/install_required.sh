#!/bin/bash
# installs all the requirements for an android build on linux x86

sudo apt-get install default-jdk sdkmanager android-sdk
export ANDROID_SDK_ROOT=/usr/lib/android-sdk
sudo mkdir /usr/lib/android-sdk/ndk # so the permissions get changed
sudo chmod -R 777 /usr/lib/android-sdk
# sdkmanager "ndk;r13b"   # install ndk
# sudo chmod -R 777 /usr/lib/android-sdk/ndk/r13b
yes | sdkmanager --license
# sudo mkdir /opt/android-sdk
# sudo mkdir /opt/android-sdk/ndk
# sudo mkdir /opt/android-sdk/ndk/r13b
# sudo mkdir /opt/android-sdk/licenses
# sdkmanager --sdk_root /usr/lib/android-sdk
# sudo chmod -R 777 /opt/android-sdk

# bash bash/android/install_android_sdk.sh
# bash bash/android/install_android_ndk.sh

bash bash/android/install_sdl.sh
source bash/android/android_copy_android_project.sh
source bash/android/copy_settings.sh
source bash/android/android_copy_sdl.sh
source bash/android/copy_source.sh
# will this update gradle? or do I need installDebug as input
# source $PWD/bash/android/gradle_set_paths.sh
cd build/android-build && bash gradlew # installDebug

# install sdl2 sdl2_image and sdl2_mixer into projects from git
# install android sdk and ndk into projects or something
# then copy android sdl project into /build/android
# next copy source over
# gradle push to phone after
# check if android sdk/ndk installed, if not install:
#   > bash install_android_sdk.sh && bash install_android_ndk.sh