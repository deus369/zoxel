#! /bin/bash

cd ~/projects/open-zoxel

make -f MakeDev -B -j24

./zoxel-dev

sleep 30