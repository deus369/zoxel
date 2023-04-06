#!/bin/bash

source bash/flecs/remove_flecs.sh

rm include/flecs/flecs.h
rm include/flecs/flecs.c

source bash/flecs/download_flecs_source.sh

echo "  > remember to build flecs"
echo "      + make build/libflecs.a"