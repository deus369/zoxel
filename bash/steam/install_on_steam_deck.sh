#!/bin/bash

source bash/util/package_util.sh

# installing on steam deck

# disable steams read only mode after an update

if is_steam_deck; then
    # the point is to reinstall make glibc linux-api-headers sdl2, only if steam readonly was enabled (if steam deck updates)
    echo "  > installing steam deck requirements"
    sudo steamos-readonly disable && sudo pacman -S make glibc linux-api-headers sdl2 && make install-required
fi

# sudo pacman -S make glibc linux-api-headers sdl2
make && make install
