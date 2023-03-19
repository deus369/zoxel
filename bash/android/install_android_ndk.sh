#!/bin/bash

# Define variables
ndk_zip_directory="build/ndk"
ndk_install_directory="build/android/ndk"

# Check the system architecture
if [[ $(uname -m) == "aarch64" ]]; then
    # ndk_url="https://github.com/lzhiyong/termux-ndk/releases/download/ndk-r23/android-ndk-r23c-aarch64.zip"
    ndk_url="https://github.com/lzhiyong/termux-ndk/releases/download/ndk-r24/android-ndk-r24-aarch64.zip"
    echo "Could not really get this to work on arm64 yet."
else
    # Other architecture, use x86_64 NDK
    ndk_url="https://dl.google.com/android/repository/android-ndk-r23-linux-x86_64.zip"
fi

# Create directories to store SDK and NDK
mkdir -p $ndk_install_directory

# Download NDK
wget -O $ndk_zip_directory.zip $ndk_url
unzip -q $ndk_zip_directory.zip -d $ndk_install_directory
rm -f $ndk_zip_directory.zip

# Set environment variables
# export ANDROID_NDK_HOME=$ndk_install_directory
# export PATH=$PATH:$ANDROID_NDK_HOME

echo "NDK downloaded successfully!"
