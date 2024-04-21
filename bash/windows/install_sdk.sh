#!/bin/bash

echo "> checking linux packages"

source bash/util/package_util.sh

# if 32 bit
# echo "> installing [mingw-w32]"
# install_first_library "mingw-w32"

echo "> installing [mingw-w64]"
install_first_library "mingw-w64"

echo "> installing [wine]"
install_first_library "wine"

# this actually needs to be just reinstalled..!
echo "> installing [glew]"
install_first_library "glew" "libglew-dev"

#if is_steam_deck; then
#    echo " > steam deck detecteed"
#    echo " > need to reinstall glew"
#    sudo pacman -S --noconfirm glew
#fi


