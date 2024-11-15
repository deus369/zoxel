#!/bin/bash
sdk_zip_directory="build/sdk.zip"
sdk_install_directory="build/android/sdk"
if [[ $(uname -m) == "aarch64" ]]; then
    sdk_url="https://github.com/lzhiyong/termux-ndk/releases/download/android-sdk/android-sdk-aarch64.zip"
    echo "Could not really get this to work on arm64 yet."
else
    # Other architecture, use x86_64 NDK
    sdk_url="https://dl.google.com/android/repository/commandlinetools-linux-7302050_latest.zip"
fi
# Create directories to store SDK and NDK
mkdir -p $sdk_install_directory
# Download SDK
wget -O $sdk_zip_directory $sdk_url
unzip -q $sdk_zip_directory -d $sdk_install_directory
rm -f $sdk_zip_directory
# Set environment variables
# export ANDROID_HOME=$sdk_install_directory # /cmdline-tools/latest
# export PATH=$PATH:$ANDROID_HOME # /bin
echo "SDK downloaded successfully!"
