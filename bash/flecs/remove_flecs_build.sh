#!/bin/bash

echo "  > removing flecs build files"

if [ -f build/flecs.o ]; then
    rm build/flecs.o
    echo "      > removed file [build/flecs.o]"
fi

if [ -f build/flecs/flecs.h ]; then
    rm include/flecs/flecs.h
    echo "      > removed file [include/flecs/flecs.h]"
fi

if [ -f build/flecs.o ]; then
    rm lib/libflecs.a
    echo "      > removed file [lib/libflecs.a]"
fi

# rm build/libflecs.a
# echo "      > removed file [build/libflecs.a]"
