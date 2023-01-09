#!/bin/bash
# run our zoxel_web

# sudo
# sudo cc -g -Wall zoxel_web.c -o zoxel_web && sudo valgrind ./zoxel_web --log
cc -g -Wall zoxel_web.c -o zoxel_web && valgrind ./zoxel_web --log

echo "Finished running server."

sleep 30