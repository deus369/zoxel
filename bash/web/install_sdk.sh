#!/bin/bash

if [ ! -d "$HOME/projects" ]; then
    mkdir "$HOME/projects"
    echo "  > created directory [~/projects]"
fi
cd $HOME/projects
echo "  > installing emscripten in [$PWD]"

if [[ -d emsdk ]]; then
	echo "  > emsdk already exists, pulling latest"
    cd emsdk
    git pull
else
	echo "  > cloning new emsdk"
    git clone https://github.com/emscripten-core/emsdk.git
    cd emsdk
    #echo 'source "$HOME/projects/emsdk/emsdk_env.sh"' >> $HOME/.bash_profile
fi

echo "  > installing latest emsdk"
./emsdk install latest
echo "  > activating latest emsdk"
./emsdk activate latest

source add_emsdk_env.sh

# sudo rm -r emsdk
# sudo rm -r /user/share/emscripten
# source ./emsdk_env.sh