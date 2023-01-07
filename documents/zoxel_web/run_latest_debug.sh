#!/bin/bash
# run our zoxel_web

sudo cc -g -Wall zoxel_web.c -o zoxel_web && sudo valgrind ./zoxel_web --log

echo "Finished running server."

sleep 30