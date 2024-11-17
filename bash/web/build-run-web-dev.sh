#!/bin/bash

cd ~/zoxel

source ~/emsdk/emsdk_env.sh

make -f MakeWebDev -B -j24

emrun --browser firefox web-dev/index.html

echo Done

sleep 30