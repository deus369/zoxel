#! /bin/bash

cd ~/zoxel

make -B -j$(nproc)

./zoxel --fullscreen

sleep 30
