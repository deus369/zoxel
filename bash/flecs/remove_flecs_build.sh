#!/bin/bash

echo "  > removing flecs build files"

rm include/flecs.h
echo "      > removed file [include/flecs.h]"

rm build/flecs.o
echo "      > removed file [build/flecs.o]"

rm build/libflecs.a
echo "      > removed file [build/libflecs.a]"

rm lib/libflecs.a
echo "      > removed file [lib/libflecs.a]"