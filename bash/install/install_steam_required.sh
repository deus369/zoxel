#!/bin/bash
# install steam things required pre build
# the other packages can be installed after in the make command

echo "  > disabling steamos readonly mode"
sudo steamos-readonly disable # disable allows installing packages with pacman

echo "  >  installing zoxel required build packages"
sudo pacman -S make gcc glibc linux-api-headers sdl2