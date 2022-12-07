#!/bin/bash

cd ~

echo "Installing EM SDK for web builds. Inside [$PWD]"
# sudo rm -r emsdk
# sudo rm -r /user/share/emscripten

if [[ -d emsdk ]]; then
	echo emsdk already exists. Git Pull!
    cd emsdk
    git pull
else
	echo Cloning new emsdk directory in $HOME
    git clone https://github.com/emscripten-core/emsdk.git
    cd emsdk
    echo 'source "$HOME/emsdk/emsdk_env.sh"' >> $HOME/.bash_profile
fi

echo "Installing latest emsdk"
./emsdk install latest

echo "Activating latest emsdk"
./emsdk activate latest

# source ./emsdk_env.sh

echo finished~