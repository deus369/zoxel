#! /bin/bash

cd ~/projects/open-zoxel

make -f MakeDev -B -j24

./zoxel-dev.x86

sleep 30