#! /bin/bash

cd ~/projects/open-zoxel

make -B -j24

./zoxel.x86 --fullscreen

sleep 30