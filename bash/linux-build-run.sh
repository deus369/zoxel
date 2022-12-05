#! /bin/bash

cd ~/zoxel

make -B -j$(nproc)

./builds/zoxel --fullscreen

sleep 30
