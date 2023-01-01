#!/bin/bash

# first go to zoxel directory
cd ../../

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
    # unzip v3.1.3.zip
    unzip -j v3.1.3.zip flecs-3.1.3/flecs.c flecs-3.1.3/flecs.h -d include/flecs

    # copy flecs.c and flecs.h from extracted directory to include/flecs
    # cp flecs-3.1.3/flecs.c include/flecs/flecs.c
    # cp flecs-3.1.3/flecs.h include/flecs/flecs.h

    # delete downloaded zip and extracted folder
    rm v3.1.3.zip
    # rm -r flecs-3.1.3
fi

echo "Flecs 3.3 is installed."