#! /bin/bash

cd ~/zoxel

make -f MakefileDev -B -j24

./zoxel-dev

sleep 30