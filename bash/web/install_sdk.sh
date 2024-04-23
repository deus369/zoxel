#!/bin/bash

web_sdk_path="build/emsdk"
if [ ! -d "build" ]; then
    mkdir "build"
    echo " + created new directory [build]"
fi
# echo " + installing emscripten in [$PWD]"
if [[ -d $web_sdk_path ]]; then
	echo " + emsdk [$web_sdk_path] exists, pulling latest"
    cd $web_sdk_path
    git pull
else
	echo "  > downloading latest emsdk to [$web_sdk_path]"
    cd build
    git clone https://github.com/emscripten-core/emsdk.git
    cd "emsdk"
    #echo 'source "$HOME/projects/emsdk/emsdk_env.sh"' >> $HOME/.bash_profile
fi

echo " + installing emsdk"
./emsdk install latest
echo " + activating emsdk"
./emsdk activate latest
echo " + adding emsdk environment variables"
source emsdk_env.sh # add_emsdk_env.sh
# return to zoxel
cd ../..

# sudo rm -r emsdk
# sudo rm -r /user/share/emscripten
# source ./emsdk_env.sh
