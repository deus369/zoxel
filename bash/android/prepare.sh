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

source bash/android/_core.sh
source bash/util/package_util.sh
source bash/android/gradle_pathing.sh

if [ is_windows ]; then
    echo "Running on Windows"
    # Set JAVA_HOME
    export JAVA_HOME="/c/ProgramData/chocolatey/lib/openjdk/tools"
    # Add JAVA_HOME/bin to PATH
    export PATH="$JAVA_HOME/bin:$PATH"
    # choco install openjdk sdkmanager -y
    install_with_choco android-sdk
    install_with_choco openjdk17 # 1
    echo "note: need to download windows sdk manually for jdk11"
    echo "  > sdkmanager cmdline tools"
    echo "      > https://developer.android.com/studio#command-tools"
    echo "  > jdk17"
    echo "      > https://www.oracle.com/java/technologies/javase/jdk17-archive-downloads.html"
    # sleep 10
else
    echo "Not running on Windows"

    echo " !!! if these fail, install yay -S sdkmanager android-sdk jdk-openjdk"
    bash bash/util/install_yay.sh
    # on ubuntu only android-sdk, default-jdk works
    # sudo apt install android-sdk default-jdk
    # ubuntu need snapd package - sudo snap install sdkmanager
    if [ has_yay ]; then
        echo "  > installing [jdk-openjdk]"
        yay -S --noconfirm jdk-openjdk
        echo "  > installing [android-sdk]"
        yay -S --noconfirm android-sdk
        echo "  > installing [sdkmanager]"
        yay -S --noconfirm sdkmanager
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
fi

# ubuntu install_sdk_manager.sh

# needed to manually install jdk-openjdk again on steam deck:
# sudo rm /etc/java-openjdk/sdp/sdp.conf.template && sudo pacman -S jdk-openjdk

clear_gradle_build
start_gradle_build

zmkdir $android_sdk_path
zmkdir $ndj_path
zmkdir "/opt/android-sdk/licenses"

# now update licenses / accept them
# yes | sdkmanager --license # accepts sdkmanager licenses in /opt/android-sdk/licenses directory
yes | sdkmanager --sdk_root=$android_sdk_path --licenses

# sdkmanager --install "ndk;r24"
# echo " > installing [ndk;r$ndk_ver]"
# sdkmanager --sdk_root=$android_sdk_path --install "ndk;r$ndk_ver"
# echo " > installing [platforms;android-$platform_ver]"
# sdkmanager --sdk_root=$android_sdk_path --install "platforms;android-$platform_ver"
# echo " > installing [platform-tools;$platform_tools_ver]"
# sdkmanager --sdk_root=$android_sdk_path --install "platform-tools;$platform_tools_ver"
# echo " > installing [build-tools;$build_tools_ver]"
# sdkmanager --sdk_root=$android_sdk_path --install "build-tools;$build_tools_ver"

# check with --list for what packages are available
# sdkmanager --sdk_root=$android_sdk_path --list

echo " > installing [ndk;24.0.8215888]"
sdkmanager --sdk_root=$android_sdk_path --install "ndk;24.0.8215888"
echo " > installing [platform-tools]"
sdkmanager --sdk_root=$android_sdk_path --install "platform-tools"
echo " > installing [platforms;android-34]"
sdkmanager --sdk_root=$android_sdk_path --install "platforms;android-34"
echo " > installing [build-tools;34.0.0]"
sdkmanager --sdk_root=$android_sdk_path --install "build-tools;34.0.0"

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
