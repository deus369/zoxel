#!/bin/bash

# this is old script, install from zoxel/bash/flecs directory

# update the flecs.c & flecs.h in include folder

echo "Installing flecs nightly from zoxel directory [$PWD]"

source bash/flecs/remove_flecs.sh

flecs_c_url="https://raw.githubusercontent.com/SanderMertens/flecs/master/flecs.c"

flecs_h_url="https://raw.githubusercontent.com/SanderMertens/flecs/master/flecs.h"

flecs_c_file_location=include/flecs/flecs.c

flecs_h_file_location=include/flecs/flecs.h

wget -O $flecs_c_file_location $flecs_c_url

wget -O $flecs_h_file_location $flecs_h_url

echo "  > downloaded current flecs source"

echo "  > remember to build flecs"
echo "      + make build/libflecs.a"