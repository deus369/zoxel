#!/bin/bash
# installs all the requirements for an android build on linux x86
# install adb, apksigner are part of android sdk tools
source bash/util/package_util.sh
source bash/android/gradle_pathing.sh
clear_gradle_build
start_gradle_build

sudo mkdir $android_sdk_path && sudo chmod -R 777 $android_sdk_path
sudo mkdir $ndk_path && sudo chmod -R 777 $ndk_path

# installs jdk, sdkmanager and sdk itself
echo "  > installing [jdk]"
install_first_library "default-jdk" "jdk-openjdk"
echo "  > installing [sdkmanager]"
install_first_library "sdkmanager"
echo "  > installing [android-sdk]"
install_first_library "android-sdk"

# license directory
sudo mkdir /opt/android-sdk/licenses && sudo chmod -R 777 /opt/android-sdk/licenses

# now update licenses / accept them
yes | sdkmanager --license # accepts sdkmanager licenses in /opt/android-sdk/licenses directory

# sdkmanager --install "ndk;r24"
echo "  > installing [platform-tools]"
sdkmanager --sdk_root=$android_sdk_path --install "platform-tools"

echo "  > installing [build-tools;30.0.3]"
sdkmanager --sdk_root=$android_sdk_path --install "build-tools;30.0.3"

echo "  > installing [platforms;android-30]"
sdkmanager --sdk_root=$android_sdk_path --install "platforms;android-30"

echo "  > installing [ndk;r21]"
sdkmanager --sdk_root=$android_sdk_path --install "ndk;r21"

# install the sdl setup for our gradle build
echo "  > installing [sdl source]"
bash bash/android/install_sdl.sh
echo "  > installing [android_project]"
source bash/android/android_copy_android_project.sh
source bash/android/android_copy_sdl.sh
echo "  > installing [settings]"
source bash/android/copy_settings.sh
echo "  > installing [source]"
source bash/android/copy_source.sh
# installs ndk automatically
echo "  > refreshing [gradlew]"
cd build/android-build && bash gradlew; cd ../..

end_gradle_build

# ===== ===== ===== ===== ===== =====
# this is manual installations if android-sdk and sdkmanager can not be installed by package manager:
# installing from aur.archlinux.org:
#   wget https://aur.archlinux.org/cgit/aur.git/snapshot/android-sdk.tar.gz
#   tar -xvf android-sdk.tar.gz
#   cd android-sdk
#   makepkg -si
# this is installing from archive:
#   wget https://archive.archlinux.org/packages/p/python-jaraco.text/python-jaraco.text-3.9.1-1-any.pkg.tar.zst
#   sudo pacman -U python-jaraco.text-3.9.1-1-any.pkg.tar.zst
# if arch, install sdkmanager from 'https://gitlab.com/fdroid/sdkmanager' manually
# ===== ===== ===== ===== ===== =====

# scrap below:
# installDebug
# install sdl2 sdl2_image and sdl2_mixer into projects from git
# install android sdk and ndk into projects or something
# then copy android sdl project into /build/android
# next copy source over
# gradle push to phone after
# check if android sdk/ndk installed, if not install:
#   > bash install_android_sdk.sh && bash install_android_ndk.sh
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
# /usr/lib/android-sdk
# used for sdk
# sudo mkdir /usr/lib/android-sdk && sudo chmod -R 777 /usr/lib/android-sdk
# sudo mkdir /usr/lib/android-sdk/ndk
# sudo mkdir /opt/android-sdk/ndk && sudo chmod -R 777 /opt/android-sdk/ndk
# android_sdk_path="$HOME/android_sdk"
# ndk_path="$android_sdk_path/ndk"
# export ANDROID_HOME="$android_sdk_path"
# export ANDROID_SDK_ROOT=$android_sdk_path
# echo "  > android sdk path is $android_sdk_path"
# echo "  > android ndk path is $ndk_path"
