#!/bin/bash

echo "  > installing zoxel"
cd $HOME/projects/zoxel
#make git-pull
git pull
make -j$(nproc)
make install