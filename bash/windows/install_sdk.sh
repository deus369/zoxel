#!/bin/bash

echo "> checking linux packages"

source bash/util/package_util.sh

# echo "> installing [mingw-w32]"
# install_first_library "mingw-w32"

echo "> installing [mingw-w64]"
install_first_library "mingw-w64"

echo "> installing [wine]"
install_first_library "wine"

# this actually needs to be just reinstalled..!
echo "> installing [glew]"
install_first_library "glew"


if is_steam_deck; then
    echo " > steam deck detecteed"
    echo " > need to reinstall glew"
    sudo pacman -S --noconfirm glew
fi

# new build folder
echo "> creating [build/windows]"
if [ ! -d build/windows ]; then
    mkdir build/windows
fi

echo "> copying [bin/*.dll]"
cp -r bin/*.dll build/windows

echo "> copying [resources]"
cp -r build/resources build/windows


