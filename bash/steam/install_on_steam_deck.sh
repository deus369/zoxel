#!/bin/bash

source bash/util/package_util.sh

# installing on steam deck

# disable steams read only mode after an update

if is_steam_deck; then
    echo "  > installing steam deck requirements"
    sudo steamos-readonly disable && sudo pacman -S make && make install-required
fi

# sudo pacman -S make glibc linux-api-headers sdl2
