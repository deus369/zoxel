#!/bin/bash

# first go to zoxel directory
cd ../../

# check if include directory exists
if [ ! -d "include" ]; then
  # create include directory if it does not exist
  mkdir -p include
fi

# check if include/flecs directory exists
if [ ! -d "include/flecs" ]; then
  # create include/flecs directory if it does not exist
  mkdir -p include/flecs
fi

# check if flecs.c and flecs.h already exist in include/flecs
if [ ! -f "include/flecs/flecs.c" ] || [ ! -f "include/flecs/flecs.h" ]; then
    echo "Installing Flecs 3.3"

    # download zip file
    wget https://github.com/SanderMertens/flecs/archive/refs/tags/v3.1.3.zip

    # extract zip file
    unzip -j v3.1.3.zip flecs-3.1.3/flecs.c flecs-3.1.3/flecs.h -d include/flecs

    # delete downloaded zip and extracted folder
    rm v3.1.3.zip
fi

echo "Flecs is installed."

# check if include/flecs directory exists
if [ ! -f "build/libflecs.a" ]; then
  echo "Make sure to build flecs first: make build/libflecs.a"
else
  echo "The flecs library has been built."
fi