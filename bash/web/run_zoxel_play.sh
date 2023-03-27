#!/bin/bash

if [ -d "../zoxel-play" ]; then
    echo "  > running zoxel-play"
    cd ../zoxel-play
    ~/projects/emsdk/upstream/emscripten/emrun --browser firefox index.html
else
    echo "  > zoxel-play not found in parent directory"
    echo "  > cd .. && git clone https://github.com/zoxel369/zoxel-play"
fi