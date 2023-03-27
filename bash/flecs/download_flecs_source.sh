#!/bin/bash

version="3.1.3"

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
    echo "  > downloading fecs [v$version]"
    # download zip file
    wget https://github.com/SanderMertens/flecs/archive/refs/tags/v$version.zip
    # extract zip file
    unzip -j v$version.zip flecs-$version/flecs.c flecs-$version/flecs.h -d include/flecs
    # delete downloaded zip and extracted folder
    rm v$version.zip
fi

echo "  > flecs [v$version] source is downloaded"

# check if include/flecs directory exists
# if [ ! -f "build/libflecs.a" ]; then
#   echo "Make sure to build flecs first: make build/libflecs.a"
# else
#   echo "The flecs library has been built."
# fi