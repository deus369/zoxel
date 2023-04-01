#!/bin/bash

echo "> checking linux packages"

source bash/util/package_util.sh

if ! has_library "gcc"; then
    install_library "gcc"
fi
# sudo apt install gcc

bash bash/sdl/install_sdl.sh