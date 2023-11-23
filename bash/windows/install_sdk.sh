#!/bin/bash

echo "> checking linux packages"

source bash/util/package_util.sh

# echo "> installing [mingw-w32]"
# install_first_library "mingw-w32"

echo "> installing [mingw-w64]"
install_first_library "mingw-w64"
