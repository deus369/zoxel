#!/bin/bash
# installs all the requirements for an android build on linux x86

# install adb for debug
# install apksigner for signing

source bash/util/package_util.sh

# /usr/lib/android-sdk
android_sdk_path="$HOME/android_sdk"
ndk_path="$android_sdk_path/ndk"
export ANDROID_HOME=$android_sdk_path
export ANDROID_SDK_ROOT=$android_sdk_path
echo "  > android sdk path is $android_sdk_path"
echo "  > android ndk path is $ndk_path"
sudo mkdir $android_sdk_path && sudo chmod -R 777 $android_sdk_path
sudo mkdir ndk_path && sudo chmod -R 777 ndk_path

# used for sdk
# sudo mkdir /usr/lib/android-sdk && sudo chmod -R 777 /usr/lib/android-sdk
# sudo mkdir /usr/lib/android-sdk/ndk
# sudo mkdir /opt/android-sdk/ndk && sudo chmod -R 777 /opt/android-sdk/ndk
# so the permissions get changed
# export ANDROID_SDK_ROOT=/usr/lib/android-sdk

install_first_library "default-jdk" "jdk-openjdk"
install_first_library "sdkmanager"
install_first_library "android-sdk"

# license directory
sudo mkdir /opt/android-sdk/licenses && sudo chmod -R 777 /opt/android-sdk/licenses
yes | sdkmanager --license
# sdkmanager --install "ndk;r24"
export ANDROID_HOME="$android_sdk_path"
sdkmanager --sdk_root=$android_sdk_path --install "platform-tools" "build-tools;30.0.3" "platforms;android-30"
sdkmanager --sdk_root=$android_sdk_path --install "ndk;r21"
# sudo cp -R /opt/android-sdk/ndk/21.0.6113669 /usr/lib/android-sdk/ndk/r21
# now update licenses / accept them

# --skippgpcheck

# if arch, install sdkmanager from 'https://gitlab.com/fdroid/sdkmanager' manually
# wget https://aur.archlinux.org/cgit/aur.git/snapshot/android-sdk.tar.gz
# tar -xvf android-sdk.tar.gz
# cd android-sdk
# makepkg -si

# something like:
# wget https://archive.archlinux.org/packages/p/python-jaraco.text/python-jaraco.text-3.9.1-1-any.pkg.tar.zst
# sudo pacman -U python-jaraco.text-3.9.1-1-any.pkg.tar.zst

# sudo apt-get install default-jdk sdkmanager android-sdk

# sdkmanager "ndk;r13b"   # install ndk
# sudo chmod -R 777 /usr/lib/android-sdk/ndk/r13b
# sudo mkdir /opt/android-sdk
# sudo mkdir /opt/android-sdk/ndk
# sudo mkdir /opt/android-sdk/ndk/r13b
# sudo mkdir /opt/android-sdk/licenses
# sdkmanager --sdk_root /usr/lib/android-sdk
# sudo chmod -R 777 /opt/android-sdk

# bash bash/android/install_android_sdk.sh
# bash bash/android/install_android_ndk.sh

# install the sdl setup for our gradle build
bash bash/android/install_sdl.sh
source bash/android/android_copy_android_project.sh
source bash/android/copy_settings.sh
source bash/android/android_copy_sdl.sh
source bash/android/copy_source.sh
# will this update gradle? or do I need installDebug as input
# source $PWD/bash/android/gradle_set_paths.sh

# installs ndk automatically
cd build/android-build && bash gradlew; cd ../..

 # installDebug
# install sdl2 sdl2_image and sdl2_mixer into projects from git
# install android sdk and ndk into projects or something
# then copy android sdl project into /build/android
# next copy source over
# gradle push to phone after
# check if android sdk/ndk installed, if not install:
#   > bash install_android_sdk.sh && bash install_android_ndk.sh
