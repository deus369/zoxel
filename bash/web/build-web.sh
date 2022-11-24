#!/bin/bash

cd ~/zoxel

source ~/emsdk/emsdk_env.sh

make -f MakeWeb -j24

echo Done

sleep 100