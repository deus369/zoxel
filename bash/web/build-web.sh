#!/bin/bash

cd ~/zoxel

source ~/emsdk/emsdk_env.sh; make -j$(nproc) web/zoxel.js

echo Done