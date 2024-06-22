#!/bin/bash

source bash/util/package_util.sh

echo "installing freetype build requirements"

# for steamdeck we must force reinstall
# sudo pacman -S --overwrite glob xorg-server-devel
install_first_library "cmake" # freetype needs cmake?
