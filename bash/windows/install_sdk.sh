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

# new build folder
echo "> creating [build/windows]"
mkdir build/windows

echo "> copying [bin/*.dll]"
cp -r bin/*.dll build/windows

echo "> copying [resources]"
cp -r build/resources build/windows


