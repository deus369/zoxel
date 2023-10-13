#!/bin/bash

echo "  > updating zoxel"
cd $HOME/projects/zoxel
#make git-pull

# check if updated?
git pull

source bash/steam/install_on_steam_deck.sh

make -j$(nproc)

make install
