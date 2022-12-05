#!/bin/bash

# update the flecs.c & flecs.h in include folder

flecs_c_url="https://raw.githubusercontent.com/SanderMertens/flecs/master/flecs.c"

flecs_h_url="https://raw.githubusercontent.com/SanderMertens/flecs/master/flecs.h"

flecs_c_file_location="$HOME/zoxel/include/flecs.c"

flecs_h_file_location="$HOME/zoxel/include/flecs.h"

wget -O $flecs_c_file_location $flecs_c_url

wget -O $flecs_h_file_location $flecs_h_url

echo Will now test flecs

cd ..

cd testing

source run_flecs_tests.sh

echo Finished updating flecs, revert if tests failed.

sleep 30
