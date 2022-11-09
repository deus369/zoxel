#!/bin/bash

cd ~/projects/zoxel

source ~/emsdk/emsdk_env.sh

make -f MakeWeb -B -j24

emrun --browser firefox web-demo/index.html

echo Done

sleep 30