#!/bin/bash

source bash/util/package_util.sh

# installing on steam deck
# disable steams read only mode after an update
# note: if valve breaks pacman again:
#   > go to '/etc/pacman.conf' and under [options] add 'SigLevel = TrustAll'

if is_steam_deck; then
    # the point is to reinstall make glibc linux-api-headers sdl2, only if steam readonly was enabled (if steam deck updates)
    result=$(sudo steamos-readonly disable 2>&1)
    if [[ ! $result =~ "already read-write" ]]; then
        echo " > fixing steamdeck keyring"
        sudo pacman-key --init
        sudo pacman-key --populate archlinux
        echo " > installing steam deck requirements"
        sudo pacman -S --noconfirm make glibc linux-api-headers sdl2
        make install-required
        make
        make install
    else
        echo " > steam deck was not updated"
    fi
fi
