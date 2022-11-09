#! /bin/bash

cd ~/projects/zoxel

make -f MakefileDev -B -j24

./zoxel-dev.x86

sleep 30