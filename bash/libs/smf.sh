#!/bin/bash

#  https://github.com/nilsgey/libsmf/archive/refs/heads/master.zip
# libsmf_url="https://github.com/stump/libsmf/archive/refs/tags/libsmf-1.3.zip"
#  "libsmf-libsmf-1.3"
libsmf_url="https://github.com/stump/libsmf/archive/refs/heads/master.zip"
# Download and extract the libsmf source
cd build
mkdir libs
cd libs

wget $libsmf_url -O libsmf.zip

unzip libsmf.zip

mv "libsmf-master" "libsmf"
cd libsmf

# Compile and install
./autogen.sh
./configure
make
sudo make install

echo "SMF library compiled and installed!"
