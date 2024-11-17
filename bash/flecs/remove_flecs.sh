#!/bin/bash

echo "  > removing flecs"

rm -R include/flecs
echo "      > removed [include/flecs] directory"

source bash/flecs/remove_flecs_build.sh