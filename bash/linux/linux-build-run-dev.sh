#! /bin/bash

cd ~/zoxel

make -f MakefileDev -B -j$(nproc)

./zoxel-dev

sleep 30