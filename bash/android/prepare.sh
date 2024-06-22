#!/bin/bash
# installs all the requirements for an android build on linux x86
# install adb, apksigner are part of android sdk tools
#
#   + open jdk
#   + sdkmanager
#   + android sdk
#
# Next, sdkmanager:
#   + licenses
#   + ndk
#   + platforms android
#   + platform tools
#   + build tools
#
# Next, we install sdl repo, and copy android template, copy over:
#   + settings
#   + source
#   + libraries
#   + resources

source bash/util/package_util.sh
source bash/android/gradle_pathing.sh

echo " !!! if these fail, install yay -S sdkmanager android-sdk dk-openjdk"
bash bash/util/install_yay.sh

if [ has_yay ]; then
    echo "  > installing [sdkmanager]"
    yay -S --noconfirm sdkmanager
    echo "  > installing [android-sdk]"
    yay -S --noconfirm android-sdk
    echo "  > installing [jdk-openjdk]"
    yay -S --noconfirm jdk-openjdk
else
    echo " ! yay does not exist"
    echo "  > installing [sdkmanager]"
    install_first_library "sdkmanager"
    echo "  > installing [android-sdk]"
    install_first_library "android-sdk"
    echo "  > installing [jdk]"
    install_first_library "default-jdk" "jdk-openjdk"
    # if failing on steamdeck, use:
    # sudo pacman -S --overwrite /etc/java-openjdk/sdp/sdp.conf.template jdk-openjdk
fi

# needed to manually install jdk-openjdk again on steam deck:
# sudo rm /etc/java-openjdk/sdp/sdp.conf.template && sudo pacman -S jdk-openjdk

clear_gradle_build
start_gradle_build

if [ ! -d $android_sdk_path ]; then
    sudo mkdir $android_sdk_path && sudo chmod -R 777 $android_sdk_path
fi
if [ ! -d $ndk_path ]; then
    sudo mkdir $ndk_path && sudo chmod -R 777 $ndk_path
fi

# license directory
if [ ! -d /opt/android-sdk/licenses ]; then
    sudo mkdir /opt/android-sdk/licenses && sudo chmod -R 777 /opt/android-sdk/licenses
fi

# now update licenses / accept them
yes | sdkmanager --license # accepts sdkmanager licenses in /opt/android-sdk/licenses directory

# sdkmanager --install "ndk;r24"
echo " > installing [ndk;r$ndk_ver]"
sdkmanager --sdk_root=$android_sdk_path --install "ndk;r$ndk_ver"
echo " > installing [platforms;android-$platform_ver]"
sdkmanager --sdk_root=$android_sdk_path --install "platforms;android-$platform_ver"
echo " > installing [platform-tools;$platform_tools_ver]"
sdkmanager --sdk_root=$android_sdk_path --install "platform-tools;$platform_tools_ver"
echo " > installing [build-tools;$build_tools_ver]"
sdkmanager --sdk_root=$android_sdk_path --install "build-tools;$build_tools_ver"

# install the sdl setup for our gradle build
echo " > installing [sdl source]"
bash bash/android/sdl/install_sdl.sh
# bash bash/sdl/install_sdl.sh
# bash bash/sdl/install_sdl_image.sh
# bash bash/sdl/install_sdl_mixer.sh
echo " > installing [android_project]"
source bash/android/sdl/copy_android_project.sh
source bash/android/sdl/copy_sdl.sh
echo " > installing [settings]"
source bash/android/sdl/copy_settings.sh
echo " > installing [source]"
source bash/android/sdl/copy_source.sh
# installs ndk automatically
echo " > refreshing [gradlew]"
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
