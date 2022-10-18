#!/bin/bash

cd ~/projects/open-zoxel

source ~/emsdk/emsdk_env.sh

make -f MakeWeb -B -j24

emrun --browser firefox zoxel.html

echo Done

sleep 30