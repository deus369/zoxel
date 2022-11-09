#!/bin/bash

cd ~/projects/zoxel

source ~/emsdk/emsdk_env.sh

make -f MakeWeb -B -j24

echo Done

sleep 100