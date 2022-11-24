#!/bin/bash

# installing emrun for first time use

# Install Python
# sudo apt-get install python3

# Install CMake (optional, only needed for tests and building Binaryen or LLVM)
# sudo apt-get install cmake

cd ~

# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git

# Enter that directory
cd emsdk

# Fetch the latest version of the emsdk (not needed the first time you clone)
git pull

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh

echo "Done installing emrun."

sleep 16