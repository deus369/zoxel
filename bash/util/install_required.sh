#!/bin/bash

echo "> checking linux packages"

source bash/util/package_util.sh

if ! has_library "gcc"; then
    install_library "gcc"
fi

if is_steam_deck; then
    if ! has_library "glibc"; then
        install_library "glibc"
    fi

    if ! has_library "lib32-glibc"; then
        install_library "lib32-glibc"
    fi

    if ! has_library "linux-headers"; then
        install_library "linux-headers"
    fi

    if ! has_library "linux-api-headers"; then
        install_library "linux-api-headers"
    fi
fi

# sudo apt install gcc

bash bash/sdl/install_sdl.sh