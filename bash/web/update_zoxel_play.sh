#!/bin/bash

web_path=build/web/zoxel # build/zoxel
if [ -f "$web_path.js"]; then
    if [ -d "../zoxel-play" ]; then
        echo "  > zoxel-play exists, copying latest web over"
        cp $web_path.js ../zoxel-play/zoxel.js
        cp $web_path.wasm ../zoxel-play/zoxel.wasm
        cp $web_path.data ../zoxel-play/zoxel.data
    else
        echo "  > zoxel-play not found in parent directory"
        echo "  > cd .. && git clone https://github.com/zoxel369/zoxel-play"
    fi
else
    echo "  - zoxel web is not built, run make web"
fi
