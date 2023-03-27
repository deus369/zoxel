#!/bin/bash

if [ -f "build/zoxel.js"]; then
    if [ -d "../zoxel-play" ]; then
        echo "  > zoxel-play exists, copying latest web over"
        cp build/zoxel.js ../zoxel-play/zoxel.js
        cp build/zoxel.wasm ../zoxel-play/zoxel.wasm
        cp build/zoxel.data ../zoxel-play/zoxel.data
    else
        echo "  > zoxel-play not found in parent directory"
        echo "  > cd .. && git clone https://github.com/zoxel369/zoxel-play"
    fi
else
    echo "  - zoxel web is not built, run make web"
fi