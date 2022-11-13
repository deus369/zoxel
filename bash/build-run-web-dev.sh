#!/bin/bash

cd ~/zoxel

source ~/emsdk/emsdk_env.sh

make -f MakeWebDev -B -j24

emrun --browser firefox web-demo-dev/index.html

echo Done

sleep 30