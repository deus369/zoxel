#! /bin/bash

cd ~/zoxel

make -f MakefileDev -B -j$(nproc)

./builds/zoxel-dev

sleep 30