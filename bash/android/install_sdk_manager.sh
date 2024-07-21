#!/bin/bash
# commandlinetools_linux_version_number=9477386_latest
# remove installed by path
# sudo rm -rf /usr/local/android-sdk
# manual sdkmanager
sudo mkdir -p /usr/local/android-sdk
if [ ! -f build/commandlinetools.zip ]; then
    echo " + downloading latest command line tools from google"
    url="https://developer.android.com/studio"
    # Use curl to fetch the page content and grep to extract the latest version number
    latest_version=$(curl -s $url | grep -oP 'commandlinetools-linux-\K[0-9]+_[a-z0-9]+' | head -1)
    echo " > version found [$latest_version]"
    # _latest
    wget https://dl.google.com/android/repository/commandlinetools-linux-${latest_version}.zip -O build/commandlinetools.zip
else
    echo " > command line tools zip already exists"
fi

if [ ! -d "/usr/local/android-sdk/cmdline-tools" ]; then
    echo " + unzipping command line tools"
    sudo mkdir -p /usr/local/android-sdk/cmdline-tools
    sudo unzip build/commandlinetools.zip -d /usr/local/android-sdk
    export PATH=$PATH:/usr/local/android-sdk/cmdline-tools/bin
    source ~/.bashrc
else
    echo " > directory exists [/usr/local/android-sdk/cmdline-tools]"
fi
