#! /bin/bash

cd ~/zoxel

make -B -j$(nproc)

make install

/usr/games/zoxel -f

# sleep 30
