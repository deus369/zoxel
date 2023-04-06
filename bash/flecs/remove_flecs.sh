#!/bin/bash

rm -R include/flecs
echo "  > removed include/flecs directory"
# rm include/flecs.h
# echo "  > removed file [include/flecs.h]"
# rm build/flecs.o
# echo "  > removed file [build/flecs.o]"
# rm build/libflecs.a
# echo "  > removed file [build/libflecs.a]"
source bash/flecs/remove_flecs_build.sh