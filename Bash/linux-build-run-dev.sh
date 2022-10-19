#! /bin/bash

cd ~/projects/open-zoxel

make -f MakeLinuxDev -B -j24

./zoxel-dev

sleep 30