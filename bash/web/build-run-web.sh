#!/bin/bash

cd ~/zoxel

source ~/emsdk/emsdk_env.sh

make -f MakeWeb -j24

emrun --browser firefox web/index.html

echo Done

sleep 30
