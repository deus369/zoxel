#! /bin/bash

cd ~/projects/zoxel

make -B -j24

./zoxel.x86 --fullscreen

sleep 30