#!/bin/bash

echo " > run with privlaged rights until windows-11 sudo command releases"

choco install git -y
choco install make -y
choco install mingw -y
choco install wget -y
choco install unzip -y

choco list

echo "couldn't find:  xdg-open, xclip, copy manually when using  make git-keys"
